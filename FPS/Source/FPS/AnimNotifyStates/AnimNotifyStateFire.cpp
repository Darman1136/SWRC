// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimNotifyStateFire.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"

void UAnimNotifyStateFire::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	UE_LOG(LogTemp, Warning, TEXT("UAnimNotifyStateFire::NotifyBegin"));
	UWorld* world = MeshComp->GetWorld();
	if (world != nullptr) {
		//ACharacter* player = UGameplayStatics::GetPlayerCharacter(world, 0);
		//if (player != nullptr && player->IsA(APlayerCharacter::StaticClass())) {
		//	Cast<APlayerCharacter>(player)->OnFire();
		//	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyBegin 2"));
		//}
	}
}

void UAnimNotifyStateFire::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyTick"));
}

void UAnimNotifyStateFire::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyAnimNotifyState::NotifyEnd"));
}



