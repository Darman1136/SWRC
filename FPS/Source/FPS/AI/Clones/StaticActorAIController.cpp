// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticActorAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "StaticActorAICharacter.h"

AStaticActorAIController::AStaticActorAIController() : Super() {
	//
}

void AStaticActorAIController::BeginPlay() {
	Super::BeginPlay();

	AnimationCycle.Sort();

	if (AutoStartCustomAnimation) {
		GetPawn()->GetWorldTimerManager().SetTimer(
			AutoStartTimerHandle, this, &AStaticActorAIController::StartAnimationCycle, AutoStartDelay / 1000.f, false);
	}
}

void AStaticActorAIController::StartAnimationCycle() {
	if (AnimationCycle.Num() > 0) {
		UAnimationAsset* Animation = AnimationCycle[0];
		PlayNextAnimationInternal(Animation);
	}
}

void AStaticActorAIController::StartAnimationCycleWithDelay(float MinRandomDelay, float MaxRandomDelay) {
	if (MinRandomDelay > 0 && MinRandomDelay < MaxRandomDelay) {
		GetPawn()->GetWorldTimerManager().SetTimer(
			AutoStartTimerHandle, this, &AStaticActorAIController::StartAnimationCycle, FMath::RandRange(MinRandomDelay, MaxRandomDelay) / 1000.f, false);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("StartAnimationCycleWithDelay: Given Delays are invalid, min: %f, max: %f"), MinRandomDelay, MaxRandomDelay);
	}
}

void AStaticActorAIController::PlayNextAnimation() {
	CurrentAnimationIndex++;
	if (CurrentAnimationIndex >= AnimationCycle.Num() && LoopCustomAnimation) {
		CurrentAnimationIndex = 0;
	}
	UAnimationAsset* Animation = AnimationCycle[CurrentAnimationIndex];
	PlayNextAnimationInternal(Animation);
}

void AStaticActorAIController::PlayNextAnimationInternal(UAnimationAsset* Animation) {
	if (Animation && PlayNext) {
		AStaticActorAICharacter* CurrentCharacter = Cast<AStaticActorAICharacter>(GetPawn());
		if (CurrentCharacter) {
			CurrentCharacter->GetMesh()->PlayAnimation(Animation, false);
		}
	}
}

void AStaticActorAIController::StopAnimationCycle() {
	PlayNext = false;
}