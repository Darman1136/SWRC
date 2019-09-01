// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneBoyAIController.h"
#include "CloneBoyAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"


ACloneBoyAIController::ACloneBoyAIController() : Super() {
	//
}

void ACloneBoyAIController::BeginPlay() {
	Super::BeginPlay();
}

void ACloneBoyAIController::LookedAtByPlayer(AActor* PlayerActor) {
	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn->IsA(ACloneBoyAICharacter::StaticClass())) {
		ACloneBoyAICharacter* CloneBoyAICharacter = Cast<ACloneBoyAICharacter>(CurrentPawn);
		if (CloneBoyAICharacter) {
			UAnimationAsset* LookAtAnimation = CloneBoyAICharacter->GetLookAtAnimation();
			float LookAtAnimationLength = CloneBoyAICharacter->GetLookAtAnimationLength();
			if (LookAtAnimation && LookAtAnimationLength > 0.f && LastTimeAnimationTriggered + LookAtAnimationLength < UGameplayStatics::GetRealTimeSeconds(GetWorld())) {
				LastTimeAnimationTriggered = UGameplayStatics::GetRealTimeSeconds(GetWorld());
				CloneBoyAICharacter->GetMesh()->PlayAnimation(LookAtAnimation, false);
			} 
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("HE LOOKED AT ME! %s"), *PlayerActor->GetName());
}

