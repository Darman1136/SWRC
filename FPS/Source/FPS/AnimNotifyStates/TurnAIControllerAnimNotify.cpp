// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnAIControllerAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/Battledroid/BattledroidAICharacter.h"


void UTurnAIControllerAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	AActor* Actor = MeshComp->GetOwner();
	if (Actor && Actor->IsA(ABattledroidAICharacter::StaticClass())) {
		FRotator Rotation = Actor->GetActorRotation();
		if (TurnDirection == ETurnDirection::TDRight) {
			Rotation.Yaw += TurnAngle;
		}
		else {
			Rotation.Yaw -= TurnAngle;
		}
		Actor->SetActorRotation(Rotation);
	}
}

