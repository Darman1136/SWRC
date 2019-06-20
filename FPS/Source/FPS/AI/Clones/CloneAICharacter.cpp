// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneAICharacter.h"
#include "FPSProjectile.h"
#include "Data/WeaponStats.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Data/DC17mBlasterStats.h"
#include "Animation/AnimInstance.h"

ACloneAICharacter::ACloneAICharacter() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));

	Muzzle = CreateDefaultSubobject<USphereComponent>(TEXT("MuzzleLocation"));
	Muzzle->SetupAttachment(WeaponMesh);

	PrimaryActorTick.bCanEverTick = true;
}

void ACloneAICharacter::BeginPlay() {
	Super::BeginPlay();

	WeaponStats = NewObject<UDC17mBlasterStats>(this);
}

void ACloneAICharacter::OnFire() {
	if (FireAnimation != NULL) {
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != NULL) {
			if (CurrentAmmo > 0) {
				CurrentAmmo--;
			} else {
				CurrentAmmo = 0;
			}

			if (ProjectileClass != NULL) {
				UWorld* const World = GetWorld();
				if (World != NULL) {
					FRotator SpawnRotation = GetControlRotation();
					SpawnRotation.Add(-2.f, -.3f, 0.f);
					const FVector SpawnLocation = Muzzle->GetComponentLocation();

					FActorSpawnParameters ActorSpawnParams;
					// ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

					AFPSProjectile* SpawnedProjectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					if (SpawnedProjectile) {
						SpawnedProjectile->SetProjectileOwner(this);
						SpawnedProjectile->SetDamage(WeaponStats->GetDamage());
						SpawnedProjectile->SetDamageType(WeaponStats->GetDamageType());
					}
				}
			}

			if (AnimInstance->GetCurrentActiveMontage() == NULL) {
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}


bool ACloneAICharacter::IsMagEmpty() {
	return false;
}

bool ACloneAICharacter::IsReadyToFire() {
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != NULL && AnimInstance->GetCurrentActiveMontage() == NULL) {
		return true;
	}
	return false;
}

