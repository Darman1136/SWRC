// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerCharacter.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UWorld* world = MeshComp->GetWorld();
	if (world != nullptr) {
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
		if (player != nullptr && player->IsA(APlayerCharacter::StaticClass())) {
			Cast<APlayerCharacter>(player)->ReloadAmmo();
		}
	}
}

void UMyAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	//
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	//
}
