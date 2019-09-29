


#include "PlayerDC15SMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <Materials/MaterialInstanceDynamic.h>
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"

UPlayerDC15SMeshComponent::UPlayerDC15SMeshComponent() : Super() {
	PrimaryComponentTick.bCanEverTick = true;

	PlayerMeshType = EPlayerMeshType::DC15S;
	VisiorEnabled = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ActualSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Meshes/HUD/DC15s/dc15s.dc15s'"));
	if (ActualSkeletalMesh.Succeeded()) {
		SetSkeletalMesh(ActualSkeletalMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ActualAnimationBlueprint(TEXT("/Game/FirstPerson/Meshes/HUD/DC15s/AB_dc15s"));
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

void UPlayerDC15SMeshComponent::Initialize(AActor* CurrentParent) {
	Super::Initialize(CurrentParent);

	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
}

void UPlayerDC15SMeshComponent::InitializeBeginPlay() {
	const int32 MaterialIndex = 2;
	UMaterialInterface* AmmoMaterial = GetMaterial(MaterialIndex);
	TArray<class UMaterialInterface*> materials = GetMaterials();
	if (AmmoMaterial != nullptr) {
		AmmoMaterialInst = UMaterialInstanceDynamic::Create(AmmoMaterial, this);
		if (AmmoMaterial != NULL) {
			SetMaterial(MaterialIndex, AmmoMaterialInst);
		}
	}
	UpdateAmmoMaterials();
}

void UPlayerDC15SMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!FMath::IsNearlyEqual(CurrentAmmo, MaxAmmo)) {
		CurrentAmmo += DeltaTime * AmmoRechargeRate;
		UpdateAmmoMaterials();
	}
	if (CurrentAmmo > MaxAmmo) {
		CurrentAmmo = MaxAmmo;
		UpdateAmmoMaterials();
	}
}

void UPlayerDC15SMeshComponent::TriggerMainAction() {
	bIsFiring = true;
	DoMainAction();
}

void UPlayerDC15SMeshComponent::TriggerStopMainAction() {
	DoStopMainAction();
}

void UPlayerDC15SMeshComponent::DoMainAction() {
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

			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = GetAnimInstance();
			if (AnimInstance != NULL) {
				if (CurrentAmmo > 0) {
					CurrentAmmo -= AmmoPerShot;
				} else {
					CurrentAmmo = 0;
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
}

void UPlayerDC15SMeshComponent::UpdateAmmoMaterials() {
	UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %d"), CurrentAmmo);
	if (AmmoMaterialInst != nullptr) {
		AmmoMaterialInst->SetVectorParameterValue("Value", FLinearColor(CurrentAmmo, 0, 0));
	}
}

bool UPlayerDC15SMeshComponent::IsMagEmpty() {
	return CurrentAmmo <= AmmoPerShot;
}
