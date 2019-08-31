


#include "PlayerWeaponMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

UPlayerWeaponMeshComponent::UPlayerWeaponMeshComponent() : Super() {}

void UPlayerWeaponMeshComponent::Initialize(AActor* CurrentParent) {
	Super::Initialize(CurrentParent);
	CurrentAmmo = MaxAmmo;
	CurrentMagAmmo = MaxMagAmmo;
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

void UPlayerWeaponMeshComponent::DoMainAction() {

}

void UPlayerWeaponMeshComponent::DoStopMainAction() {
	
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

bool UPlayerWeaponMeshComponent::IsMagEmpty() {
	return CurrentMagAmmo <= 0;
}