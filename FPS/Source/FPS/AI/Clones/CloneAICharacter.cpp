// Fill out your copyright notice in the Description page of Project Settings.

#include "CloneAICharacter.h"
#include "FPSProjectile.h"
#include "Data/WeaponStats.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

ACloneAICharacter::ACloneAICharacter() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));

	Muzzle = CreateDefaultSubobject<USphereComponent>(TEXT("MuzzleLocation"));
	Muzzle->SetupAttachment(WeaponMesh);

	PrimaryActorTick.bCanEverTick = true;
}

void ACloneAICharacter::BeginPlay() {
	Super::BeginPlay();
}

void ACloneAICharacter::OnFire() {
	if (!bIsFiring || IsMagEmpty()) {
		return;
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != NULL) {
			if (CurrentAmmo > 0) {
				CurrentAmmo--;
			} else {
				CurrentAmmo = 0;
			}

			//if (WeaponStats) {
			//	TSoftObjectPtr<UStaticMesh> ProjectileMeshPtr = WeaponStats->GetMesh();
			//	UStaticMesh* ProjectileMesh = ProjectileMeshPtr.Get();
			//	UClass* PClass = ProjectileMesh->GetClass();
			//}
			if (ProjectileClass != NULL) {
				UWorld* const World = GetWorld();
				if (World != NULL) {
					FRotator SpawnRotation = GetControlRotation();
					SpawnRotation.Add(-2.f, -.3f, 0.f);
					const FVector SpawnLocation = Muzzle->GetRelativeTransform().GetLocation();

					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					AFPSProjectile* SpawnedProjectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					if (SpawnedProjectile) {
						SpawnedProjectile->SetProjectileOwner(this);
						SpawnedProjectile->SetDamage(WeaponStats->GetDamage());
						SpawnedProjectile->SetDamageType(WeaponStats->GetDamageType());
					}
				}
			}
		}
	}
}


bool ACloneAICharacter::IsMagEmpty() {
	return false;
}


