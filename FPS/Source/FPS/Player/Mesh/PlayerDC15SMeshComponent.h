

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerWeaponMeshComponent.h"
#include "PlayerDC15SMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UPlayerDC15SMeshComponent : public UPlayerWeaponMeshComponent
{
	GENERATED_BODY()

public:
	UPlayerDC15SMeshComponent();

	virtual void Initialize(AActor* CurrentParent) override;

	virtual void InitializeBeginPlay() override;

protected:
	virtual void DoMainAction() override;

	virtual void UpdateAmmoMaterials() override;

public:
	class UMaterialInstanceDynamic* AmmoMaterialInst;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

protected:
	float MaxAmmo = 1.f;

	float CurrentAmmo = MaxAmmo;
};
