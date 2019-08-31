// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerCharacter.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UWorld* World = MeshComp->GetWorld();
	if (World != nullptr) {
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(World, 0);
		if (Player != nullptr && Player->IsA(APlayerCharacter::StaticClass())) {
			Cast<APlayerCharacter>(Player)->ReloadAmmoCount();
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
