


#include "PlayerWeaponMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance/PlayerMeshComponentAnimInstance.h"

UPlayerWeaponMeshComponent::UPlayerWeaponMeshComponent() : Super() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerWeaponMeshComponent::Initialize(AActor* CurrentParent) {
	Super::Initialize(CurrentParent);
	CurrentAmmo = MaxAmmo;
	CurrentMagAmmo = MaxMagAmmo;
}

void UPlayerWeaponMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateAnimationBlueprint();
}

void UPlayerWeaponMeshComponent::TriggerMainAction() {
	bIsFiring = true;

	if (!FMath::IsNearlyEqual(FireDelay, -1)) {
		GetWorld()->GetTimerManager().SetTimer(FireTimeHandle, this, &UPlayerWeaponMeshComponent::DoMainAction, FireDelay, true, 0.f);
	} else {
		DoMainAction();
	}
}

void UPlayerWeaponMeshComponent::TriggerStopMainAction() {
	GetWorld()->GetTimerManager().ClearTimer(FireTimeHandle);
	DoStopMainAction();
}

void UPlayerWeaponMeshComponent::DoMainAction() {}

void UPlayerWeaponMeshComponent::DoStopMainAction() {
	bIsFiring = false;
}

void UPlayerWeaponMeshComponent::TriggerReload() {
	DoReload();
}

void UPlayerWeaponMeshComponent::DoReload() {
	if (CurrentAmmo <= 0 || CurrentMagAmmo == MaxMagAmmo) {
		return;
	}

	if (ReloadAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL) {
			if (AnimInstance->GetCurrentActiveMontage() == NULL) {
				// try and play the sound if specified
				AnimInstance->Montage_Play(ReloadAnimation, 1.f);
			}
		}
	}
}

void UPlayerWeaponMeshComponent::ReloadAmmoCount() {
	CurrentMagAmmo = FMath::Min(MaxMagAmmo, CurrentAmmo);
	UpdateAmmoMaterials();
}

void UPlayerWeaponMeshComponent::UpdateAmmoMaterials() {}

void UPlayerWeaponMeshComponent::UpdateAnimationBlueprint() {
	UPlayerMeshComponentAnimInstance* AnimInstance = Cast<UPlayerMeshComponentAnimInstance>(GetAnimInstance()); 
	if (Parent && AnimInstance != NULL) {
		AnimInstance->MovementSpeed = Parent->GetVelocity().Size();
	}
}

bool UPlayerWeaponMeshComponent::IsMagEmpty() {
	return CurrentMagAmmo <= 0;
}