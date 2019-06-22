// Fill out your copyright notice in the Description page of Project Settings.

#include "FightRoomActorAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

void AFightRoomActorAICharacter::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	Accuracy = .7f;
}

void AFightRoomActorAICharacter::BeginPlay() {
	Super::BeginPlay();
	GetWeaponMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("weaponAttach_R"));
}


AActor* AFightRoomActorAICharacter::GetAimTarget() {
	return AimTarget;
}

