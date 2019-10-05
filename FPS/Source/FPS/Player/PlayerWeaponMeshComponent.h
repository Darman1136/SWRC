

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerMeshComponent.h"
#include "PlayerWeaponMeshComponent.generated.h"

/**
 *
 */
UCLASS(abstract)
class FPS_API UPlayerWeaponMeshComponent : public UPlayerMeshComponent {
	GENERATED_BODY()

public:
	UPlayerWeaponMeshComponent();

	virtual void OnComponentCreated() override;

	virtual void Initialize(AActor* CurrentParent) override;

	virtual void TriggerMainAction() override;

	virtual void TriggerStopMainAction() override;

	virtual void TriggerReload();

	virtual void ReloadAmmoCount();

	virtual void ReloadDone();

	virtual void CheckMeleeHit();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DoMainAction() override;

	virtual void DoStopMainAction() override;

	virtual void DoReload();

	virtual bool IsMagEmpty();

	virtual void UpdateAmmoMaterials();

	virtual void UpdateAnimationBlueprint();

	virtual bool CanUseMainAction() override;

	virtual bool CanUseMeleeAction() override;

	virtual bool CanUseZoom() override;

	virtual bool CanUseReload();

	virtual void ResetState() override;

	virtual void DoZoom() override;

	virtual void DoMeleeAction() override;

	virtual void SetupAttachementMeleeCollision();

protected:
	/* State variables */
	bool bIsFiring = false;
	bool bIsReloading = false;
	bool bIsZooming = false;
	/* State variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		int MaxAmmo = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		int MaxMagAmmo = 60;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		int CurrentAmmo;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		int CurrentMagAmmo;

	/** AnimMontage to play each time we reload */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* ReloadAnimation;

	UPROPERTY(EditDefaultsOnly, Category = MainAction)
		FName MuzzleSocketFName = FName("muzzleSocket");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		float FireDelay = .1f;

	UPROPERTY(EditAnywhere, Category = Melee)
		class UCapsuleComponent* MeleeCollisionCheck;

	UPROPERTY(EditAnywhere, Category = Melee)
		FName MeleeCollisionSocketName;

private:
	FTimerHandle FireTimeHandle;
};
