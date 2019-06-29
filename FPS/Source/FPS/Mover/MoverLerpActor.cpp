// Fill out your copyright notice in the Description page of Project Settings.

#include "MoverLerpActor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AMoverLerpActor::AMoverLerpActor() {
	MoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mover Mesh"));
	RootComponent = MoverMesh;

	PrimaryActorTick.bCanEverTick = true;

}

void AMoverLerpActor::BeginPlay() {
	Super::BeginPlay();

	InitializeValues();
	InitializeTriggers();
}

void AMoverLerpActor::InitializeTriggers() {
	for (AMoverTriggerBox* Trigger : TriggerColliders) {
		if (Trigger) {
			FScriptDelegate DelegateAdd;
			DelegateAdd.BindUFunction(this, "AddActorInsideCollider");
			Trigger->OnActorBeginOverlap.AddUnique(DelegateAdd);

			FScriptDelegate DelegateRemove;
			DelegateRemove.BindUFunction(this, "RemoveActorInsideCollider");
			Trigger->OnActorEndOverlap.AddUnique(DelegateRemove);
		}
	}
}

void AMoverLerpActor::InitializeValues() {
	InitialTranslation = GetTransform().GetLocation();
	InitialRotation = FRotator(GetTransform().GetRotation());
	EndTranslation = InitialTranslation + RelativeTranslation;
	EndRotation = InitialRotation + RelativeRotation;
}

void AMoverLerpActor::AddActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	bool IsImportant = false;
	for (UClass* ImportantClass : TriggerCollidersImportantActors) {
		if (ImportantClass) {
			if (OtherActor->IsA(ImportantClass)) {
				IsImportant = true;
				break;
			}
		}
	}
	
	if (IsImportant) {
		BlockingActors.Add(OtherActor);
		Triggered = true;
	}
}

void AMoverLerpActor::RemoveActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	BlockingActors.Remove(OtherActor);
}

void AMoverLerpActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if ((AlwaysOn || Triggered ) && !Paused) {
		TimeSinceMovementStart += DeltaTime;
		float LerpAlpha = TimeSinceMovementStart * 1000.f / EndMovementDelay;
		if (EnableTranslation) {
			DoTranslation(LerpAlpha);
		}
		if (EnableRotation) {
			DoRotation(LerpAlpha);
		}

		if (LerpAlpha >= 1.f) {
			Finished();
		}

	}
}

void AMoverLerpActor::DoTranslation(float LerpAlpha) {
	if (!ReverseActive || !EnableReverse) {
		TranslateForwards(LerpAlpha);
	} else {
		TranslateBackwards(LerpAlpha);
	}
}

void AMoverLerpActor::TranslateForwards(float LerpAlpha) {
	Translate(InitialTranslation, EndTranslation, LerpAlpha);
}

void AMoverLerpActor::TranslateBackwards(float LerpAlpha) {
	Translate(EndTranslation, InitialTranslation, LerpAlpha);
}

void AMoverLerpActor::Translate(FVector Start, FVector End, float LerpAlpha) {
	if (LerpAlpha < 1.f) {
		FVector LerpLocation = FMath::Lerp(Start, End, LerpAlpha);
		MoverMesh->SetRelativeLocation(LerpLocation);
	} else {
		MoverMesh->SetRelativeLocation(End);
	}
}

void AMoverLerpActor::Finished() {
	if (DelayBeforeReverse > 0.f) {
		PauseBeforeReverse(DelayBeforeReverse);
	}

	if (EnableReverse) {
		if (ReverseActive) {
			Triggered = false;
		}
		ReverseActive = !ReverseActive;
	} else {
		InitializeValues();
		Triggered = false;
	}
	TimeSinceMovementStart = 0.f;
}

void AMoverLerpActor::PauseBeforeReverse(float Delay) {
	Paused = true;
	GetWorldTimerManager().SetTimer(
		ReverseTimerHandle, this, &AMoverLerpActor::TriggerReverse, Delay / 1000.f, false);
}

void AMoverLerpActor::TriggerReverse() {
	if (CanStartReverse()) {
		Paused = false;
	} else {
		PauseBeforeReverse(50.f);
	}
}

bool AMoverLerpActor::CanStartReverse() {
	return BlockingActors.Num() == 0;
}

void AMoverLerpActor::DoRotation(float LerpAlpha) {
	if (!ReverseActive || !EnableReverse) {
		RotateForwards(LerpAlpha);
	} else {
		RotateBackwards(LerpAlpha);
	}
}

void AMoverLerpActor::RotateForwards(float LerpAlpha) {
	Rotate(InitialRotation, EndRotation, LerpAlpha);
}

void AMoverLerpActor::RotateBackwards(float LerpAlpha) {
	Rotate(EndRotation, InitialRotation, LerpAlpha);
}

void AMoverLerpActor::Rotate(FRotator Start, FRotator End, float LerpAlpha) {
	if (LerpAlpha < 1.f) {
		FRotator LerpRotation = FMath::LerpRange(Start, End, LerpAlpha);
		MoverMesh->SetRelativeRotation(LerpRotation);
	} else {
		MoverMesh->SetRelativeRotation(End);
	}
}
