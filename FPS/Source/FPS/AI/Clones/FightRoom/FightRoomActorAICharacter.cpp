// Fill out your copyright notice in the Description page of Project Settings.

#include "FightRoomActorAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

//AFightRoomActorAICharacter::AFightRoomActorAICharacter() {
	//	GetWeaponMesh()->SetupAttachment(GetMesh(), FName("weaponAttach_R"));

	// GetMuzzle()->SetRelativeLocation(FVector(134.285660f, 0.f, 31.428576f));
	// GetMuzzle()->SetSphereRadius(2)
//}

void AFightRoomActorAICharacter::BeginPlay() {
	Super::BeginPlay();
	GetWeaponMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weaponAttach_R"));
	// GetMuzzle()->SetRelativeTransform(FTransform(FVector(134.285660f, 0.f, 31.428576f)));
}


AActor* AFightRoomActorAICharacter::GetAimTarget() {
	return AimTarget;
}

