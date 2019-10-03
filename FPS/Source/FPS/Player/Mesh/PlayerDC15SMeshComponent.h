

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerWeaponMeshComponent.h"
#include "PlayerDC15SMeshComponent.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UPlayerDC15SMeshComponent : public UPlayerWeaponMeshComponent {
	GENERATED_BODY()

public:
	UPlayerDC15SMeshComponent();

	virtual void Initialize(AActor* CurrentParent) override;

	virtual void InitializeBeginPlay() override;

	virtual void TriggerMainAction() override;

	virtual void TriggerStopMainAction() override;

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void DoMainAction() override;

	virtual void UpdateAmmoMaterials() override;

	virtual bool IsMagEmpty() override;

	void ResetMainActionCooldown();

	virtual bool CanUseMainAction() override;

public:
	class UMaterialInstanceDynamic* AmmoMaterialInst;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

protected:
	float MaxAmmo = 1.f;

	float CurrentAmmo = MaxAmmo;

	UPROPERTY(EditAnywhere, Category = Gun)
		float AmmoPerShot = .3f;

	UPROPERTY(EditAnywhere, Category = Gun)
		float AmmoRechargeRate = .5f;

private:
	bool IsCoolingDown = false;

	FTimerHandle MainActionCooldownHandle;
};
