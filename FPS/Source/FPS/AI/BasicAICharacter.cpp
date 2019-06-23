// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAICharacter.h"
#include "BasicAIController.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
ABasicAICharacter::ABasicAICharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FireCooldownComplete = true;
}

// Called when the game starts or when spawned
void ABasicAICharacter::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ABasicAICharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABasicAICharacter::OnFire() {
	if (FireCooldownComplete) {
		FireCooldownComplete = false;
		GetWorld()->GetTimerManager().SetTimer(FireTimeHandle, this, &ABasicAICharacter::ResetFireCooldownComplete, FireCooldownDelay);
	}
}

bool ABasicAICharacter::IsReadyToFire() {
	return FireCooldownComplete;
}

void ABasicAICharacter::ResetFireCooldownComplete() {
	FireCooldownComplete = true;
}
