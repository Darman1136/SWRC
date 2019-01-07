// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "FPSCharacter.h"
#include <Materials/MaterialInstanceDynamic.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "Engine/World.h"
#include "TimerManager.h"
#include "FPSProjectile.h"

APlayerCharacter::APlayerCharacter() {
	CurrentAmmo = MaxAmmo;
	CurrentMagAmmo = MaxMagAmmo;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	TArray<class UMaterialInterface*> materials = Mesh1P->GetMaterials();
	if (materials[0] != nullptr) {
		AmmoDigit100 = UMaterialInstanceDynamic::Create(materials[0], this);
		if (AmmoDigit100 != NULL) {
			Mesh1P->SetMaterial(0, AmmoDigit100);
		}
	}
	if (materials[1] != nullptr) {
		AmmoDigit10 = UMaterialInstanceDynamic::Create(materials[1], this);
		if (AmmoDigit10 != NULL) {
			Mesh1P->SetMaterial(1, AmmoDigit10);
		}
	}
	if (materials[5] != nullptr) {
		AmmoDigit1 = UMaterialInstanceDynamic::Create(materials[5], this);
		if (AmmoDigit1 != NULL) {
			Mesh1P->SetMaterial(5, AmmoDigit1);
		}
	}
	if (materials[2] != nullptr) {
		AmmoChargeMag = UMaterialInstanceDynamic::Create(materials[2], this);
		if (AmmoChargeMag != NULL) {
			Mesh1P->SetMaterial(2, AmmoChargeMag);
		}
	}

	UpdateAmmoMaterials();
}

void APlayerCharacter::OnFire()
{
	if (!bIsFiring || isMagEmpty()) {
		OnFireReleased();
		return;
	}

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	// try and play the sound if specified
	/*if (FireSound != NULL)
	{
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}*/

	Super::OnFire();

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			if (CurrentAmmo > 0) {
				CurrentAmmo--;
			}
			else {
				CurrentAmmo = 0;
			}
			if (CurrentMagAmmo > 0) {
				CurrentMagAmmo--;
			}
			else {
				CurrentMagAmmo = 0;
			}
			UpdateAmmoMaterials();
		}
	}
}

bool APlayerCharacter::isMagEmpty()
{
	return CurrentMagAmmo <= 0;
}

void APlayerCharacter::UpdateAmmoMaterials()
{
	UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %d"), CurrentAmmo);
	UE_LOG(LogTemp, Warning, TEXT("CurrentMagAmmo: %d"), CurrentMagAmmo);
	if (AmmoDigit100 != nullptr) {
		if (CurrentAmmo >= 100) {
			AmmoDigit100->SetVectorParameterValue("Value", FLinearColor((CurrentAmmo / 100) % 10, 0, 0));
		}
		else {
			AmmoDigit100->SetVectorParameterValue("Value", FLinearColor(0, 0, 0));
		}
	}
	if (AmmoDigit10 != nullptr) {
		if (CurrentAmmo >= 10) {
			AmmoDigit10->SetVectorParameterValue("Value", FLinearColor((CurrentAmmo / 10) % 10, 0, 0));
		}
		else {
			AmmoDigit10->SetVectorParameterValue("Value", FLinearColor(0, 0, 0));
		}
	}
	if (AmmoDigit1 != nullptr) {
		AmmoDigit1->SetVectorParameterValue("Value", FLinearColor(CurrentAmmo % 10, 0, 0));
	}
	if (AmmoChargeMag != nullptr) {
		if (CurrentMagAmmo == MaxMagAmmo) {
			AmmoChargeMag->SetVectorParameterValue("Value", FLinearColor(21, 0, 0));
		}
		else {
			AmmoChargeMag->SetVectorParameterValue("Value", FLinearColor(FMath::CeilToInt(CurrentMagAmmo / 3.f), 0, 0));
		}
	}
}

void APlayerCharacter::ReloadAmmo()
{
	UE_LOG(LogTemp, Log, TEXT("ReloadAmmo"));
	CurrentMagAmmo = MaxMagAmmo;
	UpdateAmmoMaterials();
}

void APlayerCharacter::OnReload()
{
	if (CurrentAmmo <= 0 || CurrentMagAmmo == MaxMagAmmo) {
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnReload"));
	// try and play the sound if specified
	if (ReloadSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (ReloadAnimation != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ReloadAnimation != NULL"));
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			if (AnimInstance->GetCurrentActiveMontage() == NULL) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AnimInstance != NULL"));
				AnimInstance->Montage_Play(ReloadAnimation, 1.f);
			}
		}
	}
}