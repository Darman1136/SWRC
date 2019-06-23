// Fill out your copyright notice in the Description page of Project Settings.

#include "BattledroidAIController.h"
#include "BattledroidAICharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/BattleDroid/BattledroidAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Data/EnemyStats/BattleDroidStats.h"
#include "Weapon/Projectile/DamageAreaEnum.h"

const FName ABattledroidAIController::BoneNameHead = FName("Head");
const float ABattledroidAIController::FreakOutByHeadshotChance = 0.07f;

ABattledroidAIController::ABattledroidAIController() : Super() {
	//
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

			BattleDroidStats = NewObject<UBattleDroidStats>(this);
			if (BattleDroidStats) {
				MaxHealth = BattleDroidStats->GetMaxHealth();
				Health = BattleDroidStats->GetHealth();
			}
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

	UObject* PlayerObject = BlackboardComp->GetValueAsObject(ABasicAIController::BKTarget);
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

void ABattledroidAIController::TakeDamage(AActor * AttackingActor, EWeaponDamageType DamageType, float amount, const FHitResult & Hit)
{
	Super::TakeDamage(AttackingActor, DamageType, amount, Hit);

	DeathByHeadshot = GetTakenDamageAreaByBoneName(Hit.BoneName) == EDamageArea::DAHead;

	if (Health == 0) {
		OnDeath();
	}
}



EDamageArea ABattledroidAIController::GetTakenDamageAreaByBoneName(FName Bone)
{
	if (Bone == BoneNameHead) {
		return EDamageArea::DAHead;
	}
	return Super::GetTakenDamageAreaByBoneName(Bone);
}

float ABattledroidAIController::GetTakenDamageMultiplier(FName Bone)
{
	EDamageArea DamageArea = GetTakenDamageAreaByBoneName(Bone);

	float Multiplier;
	if (DamageArea == EDamageArea::DAHead) {
		Multiplier = 2.f;
	}
	else {
		Multiplier = Super::GetTakenDamageMultiplier(Bone);
	}

	return Multiplier;
}

void ABattledroidAIController::OnDeath()
{
	Super::OnDeath();
	BattledroidAnimInstance->WalkSpeed = 0.f;
	BattledroidAnimInstance->StrafeSpeed = 0.f;
	BattledroidAnimInstance->IsWalking = false;
	BattledroidAnimInstance->InAction = false;
	if (DeathByHeadshot && FMath::RandRange(0.f, 1.f) < FreakOutByHeadshotChance) {
		BattledroidAnimInstance->DeathByHeadshot = DeathByHeadshot;
		APawn* Pawn = GetPawn();
		if (Pawn->IsA(ABattledroidAICharacter::StaticClass())) {
			ABattledroidAICharacter* Character = Cast<ABattledroidAICharacter>(Pawn);
			if (Character) {
				USkeletalMeshComponent* SMesh = Character->GetMesh();
				SMesh->HideBoneByName(BoneNameHead, EPhysBodyOp::PBO_Term);
			}
		}
	}
	BattledroidAnimInstance->Alive = false;
}
