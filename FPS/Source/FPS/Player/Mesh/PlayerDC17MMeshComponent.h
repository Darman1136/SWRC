

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerWeaponMeshComponent.h"
#include "PlayerDC17MMeshComponent.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UPlayerDC17MMeshComponent : public UPlayerWeaponMeshComponent {
	GENERATED_BODY()

public:
	UPlayerDC17MMeshComponent();

	virtual void Initialize(AActor* CurrentParent) override;

	virtual void InitializeBeginPlay() override;

protected:
	virtual void DoMainAction() override;

	virtual void UpdateAmmoMaterials() override;

	virtual void SetupAttachementMeleeCollision() override;

public:
	class UMaterialInstanceDynamic* AmmoDigit100;

	class UMaterialInstanceDynamic* AmmoDigit10;

	class UMaterialInstanceDynamic* AmmoDigit1;

	class UMaterialInstanceDynamic* AmmoChargeMag;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

};
