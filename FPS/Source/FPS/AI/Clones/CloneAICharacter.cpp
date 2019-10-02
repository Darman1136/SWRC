// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneAICharacter.h"
#include "Data/WeaponStats.h"
#include "Data/DC17mBlasterStats.h"

ACloneAICharacter::ACloneAICharacter() {
	PrimaryActorTick.bCanEverTick = true;
}

void ACloneAICharacter::BeginPlay() {
	Super::BeginPlay();

	// WeaponStats = NewObject<UDC17mBlasterStats>(this);
}
