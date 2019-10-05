


#include "PlayerWeaponMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance/PlayerMeshComponentAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "AI/BasicAICharacter.h"

UPlayerWeaponMeshComponent::UPlayerWeaponMeshComponent() : Super() {
	PrimaryComponentTick.bCanEverTick = true;

	MeleeCollisionCheck = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeCollisionCheck"));
}

void UPlayerWeaponMeshComponent::OnComponentCreated() {
	Super::OnComponentCreated();
	SetupAttachementMeleeCollision();
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
	if (!CanUseReload()) {
		return;
	}
	bIsReloading = true;
	bIsZooming = false;
}

void UPlayerWeaponMeshComponent::ReloadAmmoCount() {
	CurrentMagAmmo = FMath::Min(MaxMagAmmo, CurrentAmmo);
	UpdateAmmoMaterials();
}

void UPlayerWeaponMeshComponent::ReloadDone() {
	bIsReloading = false;
}

void UPlayerWeaponMeshComponent::DoMeleeAction() {
	if (!CanUseMeleeAction()) {
		return;
	}
	Super::DoMeleeAction();
	bIsZooming = false;
}

void UPlayerWeaponMeshComponent::UpdateAmmoMaterials() {}

void UPlayerWeaponMeshComponent::UpdateAnimationBlueprint() {
	UPlayerMeshComponentAnimInstance* AnimInstance = Cast<UPlayerMeshComponentAnimInstance>(GetAnimInstance());
	if (Parent && AnimInstance != NULL) {
		AnimInstance->MovementSpeed = Parent->GetVelocity().Size();
		AnimInstance->IsFiring = bIsFiring;
		AnimInstance->IsReloading = bIsReloading;
		AnimInstance->IsZooming = bIsZooming;
		AnimInstance->IsActive = bIsActive;
		AnimInstance->IsLoading = bIsLoading;
		AnimInstance->IsHolstering = bIsHolstering;
		AnimInstance->IsMeleeing = bIsMeleeing;
	}
}

bool UPlayerWeaponMeshComponent::IsMagEmpty() {
	return CurrentMagAmmo <= 0;
}

bool UPlayerWeaponMeshComponent::CanUseMainAction() {
	return Super::CanUseMainAction() && !IsMagEmpty() && !bIsReloading;
}

bool UPlayerWeaponMeshComponent::CanUseMeleeAction() {
	return Super::CanUseMeleeAction() && !bIsReloading && !bIsMeleeing;
}

bool UPlayerWeaponMeshComponent::CanUseZoom() {
	return Super::CanUseZoom() && !bIsReloading && !bIsMeleeing;
}

bool UPlayerWeaponMeshComponent::CanUseReload() {
	return !bIsReloading && !bIsMeleeing && CurrentAmmo > 0 && CurrentMagAmmo != MaxMagAmmo;
}

void UPlayerWeaponMeshComponent::ResetState() {
	Super::ResetState();
	bIsFiring = false;
	bIsReloading = false;
	bIsZooming = false;
}

void UPlayerWeaponMeshComponent::DoZoom() {
	if (!CanUseZoom()) {
		bIsZooming = false;
	} else {
		bIsZooming = !bIsZooming;
	}
}

void UPlayerWeaponMeshComponent::SetupAttachementMeleeCollision() {
	if (MeleeCollisionCheck && !MeleeCollisionSocketName.IsNone()) {
		MeleeCollisionCheck->SetupAttachment(this, MeleeCollisionSocketName);
	}
}

void UPlayerWeaponMeshComponent::CheckMeleeHit() {
	if (MeleeCollisionCheck) {
		TArray<FOverlapInfo> OverlappingAIInfo = MeleeCollisionCheck->GetOverlapInfos();

		float ClosestOverlappingActorDistance = 9999999.f;
		ABasicAICharacter* ClosestOverlappingActor = nullptr;
		FHitResult ClosestOverlappingActorHit;
		for (FOverlapInfo Info : OverlappingAIInfo) {
			FHitResult Hit = Info.OverlapInfo;
			if (Hit.Actor.IsValid() && Hit.Actor.Get()->IsA(ABasicAICharacter::StaticClass())) {
				if (Hit.Distance < ClosestOverlappingActorDistance) {
					ClosestOverlappingActorHit = Hit;
					ClosestOverlappingActorDistance = Hit.Distance;
					ClosestOverlappingActor = Cast<ABasicAICharacter>(Hit.Actor.Get());
				}
			}
		}

		if (ClosestOverlappingActor) {
			ABasicAIController* OverlappingController = ClosestOverlappingActor->GetCastedController<ABasicAIController>();
			OverlappingController->TakeDamageAI(Parent, EWeaponDamageType::WDTMelee, 200.f, ClosestOverlappingActorHit);
		}
	}
}

