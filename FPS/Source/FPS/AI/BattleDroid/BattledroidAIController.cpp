// Fill out your copyright notice in the Description page of Project Settings.

#include "BattledroidAIController.h"
#include "BattledroidAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/BattleDroid/BattledroidAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ABattledroidAIController::ABattledroidAIController() {

}

void ABattledroidAIController::BeginPlay() {
	Super::BeginPlay();
	APawn* Pawn = GetPawn();
	if (Pawn->IsA(ABattledroidAICharacter::StaticClass())) {
		ABattledroidAICharacter* Character = Cast<ABattledroidAICharacter>(Pawn);
		if (Character) {
			USkeletalMeshComponent* SMesh = Character->GetMesh();
			if (SMesh) {
				UAnimInstance* AnimInstance = SMesh->GetAnimInstance();

				if (AnimInstance && AnimInstance->IsA(UBattledroidAnimInstance::StaticClass())) {
					BattledroidAnimInstance = Cast<UBattledroidAnimInstance>(AnimInstance);
				}
			}

			CharacterMovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
		}
	}
}

void ABattledroidAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	bool InAction = false;

	FVector CurrentVelocity = GetPawn()->GetVelocity();
	UE_LOG(LogTemp, Warning, TEXT("     Vel: %s"), *CurrentVelocity.ToString());

	if (!CurrentVelocity.IsNearlyZero()) {
		float MaxSpeed = CharacterMovementComponent->MaxWalkSpeed;
		FVector Norm = CurrentVelocity / MaxSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Norm Vel: %s"), *Norm.ToString());

		InAction = true;
		BattledroidAnimInstance->IsWalking = true;
		BattledroidAnimInstance->WalkSpeed = Norm.GetMax();
	}
	else {
		BattledroidAnimInstance->IsWalking = false;
	}


	BattledroidAnimInstance->InAction = InAction;
}

