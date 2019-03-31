// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticActorNextAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/Clones/StaticActorAICharacter.h"
#include "AI/Clones/StaticActorAIController.h"

void UStaticActorNextAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	AActor* Actor = MeshComp->GetOwner();
	if (Actor && Actor->IsA(AStaticActorAICharacter::StaticClass())) {
		AStaticActorAICharacter* StaticActorCharacter = Cast<AStaticActorAICharacter>(Actor);
		AStaticActorAIController* StaticActorController = StaticActorCharacter->GetCastedController<AStaticActorAIController>();
		StaticActorController->PlayNextAnimation();
	}
}


