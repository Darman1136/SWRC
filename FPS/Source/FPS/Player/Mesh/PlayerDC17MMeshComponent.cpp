


#include "PlayerDC17MMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <Materials/MaterialInstanceDynamic.h>
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "FPSProjectile.h"
#include "DrawDebugHelpers.h"

UPlayerDC17MMeshComponent::UPlayerDC17MMeshComponent() : Super() {
	PlayerMeshType = EPlayerMeshType::BABY;
	VisiorEnabled = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ActualSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Meshes/HUD/DC17mBlaster/dc17mBlaster_splitTextures.dc17mBlaster_splitTextures'"));
	if (ActualSkeletalMesh.Succeeded()) {
		SetSkeletalMesh(ActualSkeletalMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ActualAnimationBlueprint(TEXT("/Game/FirstPerson/Meshes/HUD/DC17mBlaster/AB_DC17mBlaster"));
	if (ActualAnimationBlueprint.Succeeded()) {
		SetAnimInstanceClass(ActualAnimationBlueprint.Class);
	}

	SetOnlyOwnerSee(true);
	bCastDynamicShadow = false;
	CastShadow = false;
	RelativeRotation = FRotator(0.f, 0.f, -5.f);
	RelativeLocation = FVector(6.f, 0.f, 0.f);
	RelativeScale3D = FVector(0.3f, 0.3f, 0.3f);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
}

void UPlayerDC17MMeshComponent::Initialize(AActor* CurrentParent) {
	Super::Initialize(CurrentParent);

	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
}

void UPlayerDC17MMeshComponent::InitializeBeginPlay() {
	TArray<class UMaterialInterface*> materials = GetMaterials();
	if (materials.Num() != 0) {
		if (materials[0] != nullptr) {
			AmmoDigit100 = UMaterialInstanceDynamic::Create(materials[0], this);
			if (AmmoDigit100 != NULL) {
				SetMaterial(0, AmmoDigit100);
			}
		}
		if (materials[1] != nullptr) {
			AmmoDigit10 = UMaterialInstanceDynamic::Create(materials[1], this);
			if (AmmoDigit10 != NULL) {
				SetMaterial(1, AmmoDigit10);
			}
		}
		if (materials[5] != nullptr) {
			AmmoDigit1 = UMaterialInstanceDynamic::Create(materials[5], this);
			if (AmmoDigit1 != NULL) {
				SetMaterial(5, AmmoDigit1);
			}
		}
		if (materials[2] != nullptr) {
			AmmoChargeMag = UMaterialInstanceDynamic::Create(materials[2], this);
			if (AmmoChargeMag != NULL) {
				SetMaterial(2, AmmoChargeMag);
			}
		}
	}
	UpdateAmmoMaterials();
}

void UPlayerDC17MMeshComponent::DoMainAction() {
	Super::DoMainAction();
	if (IsMagEmpty()) {
		TriggerStopMainAction();
		return;
	}

	if (MainActionAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL && AnimInstance->GetCurrentActiveMontage() == NULL) {
			AnimInstance->Montage_Play(MainActionAnimation, 1.f);
		}
	}
	// try and play a firing animation if specified
	if (MainActionAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL) {
			if (CurrentAmmo > 0) {
				CurrentAmmo--;
			} else {
				CurrentAmmo = 0;
			}
			if (CurrentMagAmmo > 0) {
				CurrentMagAmmo--;
			} else {
				CurrentMagAmmo = 0;
			}
			UpdateAmmoMaterials();

			if (ProjectileClass != NULL) {
				UWorld* const World = GetWorld();
				if (World != NULL) {
					FRotator SpawnRotation = GetComponentRotation();
					const FTransform MuzzleTransform = GetSocketTransform(MuzzleSocketFName);
					const FVector SpawnLocation = MuzzleTransform.GetLocation();
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					ActorSpawnParams.Owner = Parent;

					AFPSProjectile* SpawnedProjectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					if (SpawnedProjectile) {
						// TODO find a way to store gun values nicely (don't seem to get datatables to work right)
						SpawnedProjectile->SetDamage(30);
						SpawnedProjectile->SetDamageType(EWeaponDamageType::WDTEnergy);
					}
				}
			}
		}
	}
}

void UPlayerDC17MMeshComponent::UpdateAmmoMaterials() {
	UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %d"), CurrentAmmo);
	UE_LOG(LogTemp, Warning, TEXT("CurrentMagAmmo: %d"), CurrentMagAmmo);
	if (AmmoDigit100 != nullptr) {
		if (CurrentAmmo >= 100) {
			AmmoDigit100->SetVectorParameterValue("Value", FLinearColor((CurrentAmmo / 100) % 10, 0, 0));
		} else {
			AmmoDigit100->SetVectorParameterValue("Value", FLinearColor(0, 0, 0));
		}
	}
	if (AmmoDigit10 != nullptr) {
		if (CurrentAmmo >= 10) {
			AmmoDigit10->SetVectorParameterValue("Value", FLinearColor((CurrentAmmo / 10) % 10, 0, 0));
		} else {
			AmmoDigit10->SetVectorParameterValue("Value", FLinearColor(0, 0, 0));
		}
	}
	if (AmmoDigit1 != nullptr) {
		AmmoDigit1->SetVectorParameterValue("Value", FLinearColor(CurrentAmmo % 10, 0, 0));
	}
	if (AmmoChargeMag != nullptr) {
		if (CurrentMagAmmo == MaxMagAmmo) {
			AmmoChargeMag->SetVectorParameterValue("Value", FLinearColor(21, 0, 0));
		} else {
			AmmoChargeMag->SetVectorParameterValue("Value", FLinearColor(FMath::CeilToInt(CurrentMagAmmo / 3.f), 0, 0));
		}
	}
}
