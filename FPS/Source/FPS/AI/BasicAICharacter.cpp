// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAICharacter.h"
#include "BasicAIController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FPSProjectile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasicAICharacter::ABasicAICharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetMesh());

	Muzzle = CreateDefaultSubobject<USphereComponent>(TEXT("MuzzleLocation"));
	Muzzle->SetupAttachment(WeaponMesh);

	FireCooldownComplete = true;
}

// Called when the game starts or when spawned
void ABasicAICharacter::BeginPlay() {
	Super::BeginPlay();
	AttachWeaponMeshToBone(WeaponMeshAttachBone);
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
	if (FireAnimation != NULL) {
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != NULL) {
			if (CurrentAmmo > 0) {
				CurrentAmmo--;
			} else {
				CurrentAmmo = 0;
			}

			FireProjectile();

			if (AnimInstance->GetCurrentActiveMontage() == NULL) {
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}

void ABasicAICharacter::FireProjectile(bool UseWeaponRotation) {
	if (ProjectileClass != NULL) {
		UWorld* const World = GetWorld();
		if (World != NULL) {
			FRotator SpawnRotation;
			if (!UseWeaponRotation) {
				SpawnRotation = GetControlRotation();
			} else {
				SpawnRotation = Muzzle->GetComponentRotation();
			}
			SpawnRotation.Add(GetRandomDeviation(Accuracy), GetRandomDeviation(Accuracy), GetRandomDeviation(Accuracy));
			const FVector SpawnLocation = Muzzle->GetComponentLocation();

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ActorSpawnParams.Owner = this;

			AFPSProjectile* SpawnedProjectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (SpawnedProjectile) {
				SpawnedProjectile->SetDamage(30);
				SpawnedProjectile->SetDamageType(EWeaponDamageType::WDTEnergy);
			}
		}
	}
}

bool ABasicAICharacter::IsReadyToFire() {
	return FireCooldownComplete;
}

void ABasicAICharacter::ResetFireCooldownComplete() {
	FireCooldownComplete = true;
}

bool ABasicAICharacter::IsMagEmpty() {
	return false;
}

float ABasicAICharacter::GetRandomDeviation(float CurrentAccuracy) {
	float RandomDeviation = FMath::RandRange(0.f - (1.f - CurrentAccuracy), 0.f + 1.f - CurrentAccuracy);
	return MaxAccuracyDeviation * RandomDeviation;
}

void ABasicAICharacter::AttachWeaponMeshToBone(FName Bone) {
	if (!Bone.IsNone()) {
		GetWeaponMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, Bone);
	}
}