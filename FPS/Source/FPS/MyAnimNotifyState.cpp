// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerCharacter.h"

void UMyAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyBegin"));
	UWorld* world = MeshComp->GetWorld();
	if (world != nullptr) {
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
		if (player != nullptr && player->IsA(APlayerCharacter::StaticClass())) {
			Cast<APlayerCharacter>(player)->ReloadAmmo();
			UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyBegin 2"));
		}
	}
}

void UMyAnimNotifyState::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyTick"));
}

void UMyAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyEnd"));
}
