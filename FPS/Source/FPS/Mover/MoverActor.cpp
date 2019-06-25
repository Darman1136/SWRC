// Fill out your copyright notice in the Description page of Project Settings.

#include "MoverActor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AMoverActor::AMoverActor() {
	MoverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mover Mesh"));

	PrimaryActorTick.bCanEverTick = true;
}

void AMoverActor::BeginPlay() {
	Super::BeginPlay();

	InitialTransform = GetTransform();
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
						PauseBeforeReverse();
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

void AMoverActor::PauseBeforeReverse() {
	Paused = true;
	GetWorldTimerManager().SetTimer(
		ReverseTranslationTimerHandle, this, &AMoverActor::Reverse, DelayBeforeReverseTranslation / 1000.f, false);
}

void AMoverActor::Reverse() {
	Paused = false;
}

void AMoverActor::Rotate(float DeltaTime) {
	MoverMesh->AddLocalRotation(FRotator(Rotation.Y * DeltaTime, Rotation.Z * DeltaTime, Rotation.X * DeltaTime));
}