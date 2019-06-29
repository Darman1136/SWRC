// Fill out your copyright notice in the Description page of Project Settings.

#include "MoverActor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

/* Deprecated, use MoverLerpActor instead */

AMoverActor::AMoverActor() : Super() {
	MoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mover Mesh"));
	RootComponent = MoverMesh;

	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("Deprecated, use MoverLerpActor instead"));
}

void AMoverActor::BeginPlay() {
	Super::BeginPlay();

	InitialTransform = GetTransform();

	for (AMoverTriggerBox* Trigger : ReverseColliders) {
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

void AMoverActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if ((AlwaysOn || Triggered) && !Paused && !DoneMoveOnce) {
		Move(DeltaTime);
	}
}

/* Trigger needs to be reset once the animation finished */
void AMoverActor::TriggerMover() {
	Triggered = true;
}

void AMoverActor::Move(float DeltaTime) {
	if (MoverMesh) {
		if (EnableTranslation) {
			Translate(DeltaTime);
		}
		if (EnableRotation) {
			Rotate(DeltaTime);
		}
	}
}

void AMoverActor::DoTranslation(FVector LocalVectorToAdd) {
	MoverMesh->AddLocalOffset(LocalVectorToAdd);
}

void AMoverActor::Translate(float DeltaTime) {
	FVector Offset = FVector(Translation.X * DeltaTime, Translation.Y * DeltaTime, Translation.Z * DeltaTime);

	if (LimitTranslation) {
		// are we moving in negative direction
		float AlreadyMovedInX;
		if (Translation.X >= 0) {
			AlreadyMovedInX = GetTransform().GetLocation().X - InitialTransform.GetLocation().X;
		} else {
			AlreadyMovedInX = InitialTransform.GetLocation().X - GetTransform().GetLocation().X;
		}

		if (!IsReversingTranlation) {
			if (AlreadyMovedInX > MaxTranslation) {
				if (ReversableTranslation) {
					IsReversingTranlation = true;

					if (DelayBeforeReverseTranslation > 0) {
						PauseBeforeReverse(DelayBeforeReverseTranslation);
						Offset = FVector();
					} else {
						Offset *= -1;
					}
				} else {
					DoneMoveOnce = true;
				}
			}
		} else {
			if (AlreadyMovedInX > 0) {
				Offset *= -1;
			} else {
				IsReversingTranlation = false;
				Triggered = false;
			}
		}
		// UE_LOG(LogTemp, Warning, TEXT("Reversing: %s - Moved: %f"), (IsReversingTranlation ? TEXT("True") : TEXT("False")), AlreadyMovedInX);
	}

	DoTranslation(Offset);
}

void AMoverActor::PauseBeforeReverse(float Delay) {
	Paused = true;
	GetWorldTimerManager().SetTimer(
		ReverseTranslationTimerHandle, this, &AMoverActor::Reverse, Delay / 1000.f, false);
}

bool AMoverActor::CanStartReverse() {
	return ReverseBlockingActors.Num() == 0;
}

void AMoverActor::Reverse() {
	if (CanStartReverse()) {
		Paused = false;
	} else {
		PauseBeforeReverse(50.f);
	}
}

void AMoverActor::Rotate(float DeltaTime) {
	MoverMesh->AddLocalRotation(FRotator(Rotation.Y * DeltaTime, Rotation.Z * DeltaTime, Rotation.X * DeltaTime));
}

void AMoverActor::AddActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	// UE_LOG(LogTemp, Warning, TEXT("ADD: %s, %s"), *SelfActor->GetName(), *OtherActor->GetName());
	ReverseBlockingActors.Add(OtherActor);
}

void AMoverActor::RemoveActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {
	// UE_LOG(LogTemp, Warning, TEXT("REMOVE: %s, %s"), *SelfActor->GetName(), *OtherActor->GetName());
	ReverseBlockingActors.Remove(OtherActor);
}
