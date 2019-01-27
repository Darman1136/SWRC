// Fill out your copyright notice in the Description page of Project Settings.

#include "BattledroidAIController.h"
#include "BattledroidAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/BattleDroid/BattledroidAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSCharacter.h"
#include "Kismet/KismetMathLibrary.h"

ABattledroidAIController::ABattledroidAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

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
	const FRotator CurrentRotation = GetPawn()->GetActorRotation();
	CurrentVelocity = CurrentRotation.UnrotateVector(CurrentVelocity);
	//UE_LOG(LogTemp, Warning, TEXT("     Vel: %s"), *CurrentVelocity.ToString());

	UObject* PlayerObject =  BlackboardComp->GetValueAsObject(ABasicAIController::BKTarget);
	if (PlayerObject && PlayerObject->IsA(AFPSCharacter::StaticClass())) {
		AFPSCharacter* Player = Cast<AFPSCharacter>(PlayerObject);
		InAction = true;

		TurnHeadToObject(Player);
	}

	if (!CurrentVelocity.IsNearlyZero()) {
		float MaxSpeed = CharacterMovementComponent->MaxWalkSpeed;
		FVector Norm = CurrentVelocity / MaxSpeed;
		//UE_LOG(LogTemp, Warning, TEXT("Norm Vel: %s"), *Norm.ToString());

		InAction = true;
		BattledroidAnimInstance->IsWalking = true;

		float Max = Norm.GetAbsMax();
		if (FMath::IsNearlyEqual(Max, FMath::Abs(Norm.X))) {
			BattledroidAnimInstance->WalkSpeed = Norm.X;
			BattledroidAnimInstance->StrafeSpeed = 0.f;
		}
		else if (FMath::IsNearlyEqual(Max, FMath::Abs(Norm.Y))) {
			BattledroidAnimInstance->WalkSpeed = 0.f;
			BattledroidAnimInstance->StrafeSpeed = Norm.Y;
		}

		// UE_LOG(LogTemp, Warning, TEXT("%s %s"), *FString::SanitizeFloat(BattledroidAnimInstance->WalkSpeed), *FString::SanitizeFloat(BattledroidAnimInstance->StrafeSpeed));
	}
	else {
		BattledroidAnimInstance->IsWalking = false;
	}


	BattledroidAnimInstance->InAction = InAction;
}
