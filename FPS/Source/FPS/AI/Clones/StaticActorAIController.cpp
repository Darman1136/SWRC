// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticActorAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "StaticActorAICharacter.h"

AStaticActorAIController::AStaticActorAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void AStaticActorAIController::BeginPlay() {
	Super::BeginPlay();

	AnimationCycle.Sort();

	if (AutoStartCustomAnimation) {
		GetPawn()->GetWorldTimerManager().SetTimer(
			AutoStartTimerHandle, this, &AStaticActorAIController::StartAnimationCycle, AutoStartDelay, false);
	}
}

void AStaticActorAIController::StartAnimationCycle() {
	if (AnimationCycle.Num() > 0) {
		UAnimationAsset* Animation = AnimationCycle[0];
		PlayNextAnimationInternal(Animation);
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
		AStaticActorAICharacter* Character = Cast<AStaticActorAICharacter>(GetPawn());
		if (Character) {
			Character->GetMesh()->PlayAnimation(Animation, false);
		}
	}
}

void AStaticActorAIController::StopAnimationCycle() {
	PlayNext = false;
}