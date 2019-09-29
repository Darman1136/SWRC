

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerMeshComponent.h"
#include "PlayerWeaponMeshComponent.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UPlayerWeaponMeshComponent : public UPlayerMeshComponent {
	GENERATED_BODY()

public:
	UPlayerWeaponMeshComponent();

	virtual void Initialize(AActor* CurrentParent) override;

	virtual void TriggerMainAction() override;

	virtual void TriggerStopMainAction() override;

	virtual void TriggerReload();

	virtual void ReloadAmmoCount();

protected:
	virtual void DoMainAction() override;

	virtual void DoStopMainAction() override;

	virtual void DoReload();

	virtual bool IsMagEmpty();

	virtual void UpdateAmmoMaterials();

protected:
	bool bIsFiring = false;

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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun, meta = (AllowPrivateAccess = true))
		float FireDelay = .1f;

	FTimerHandle FireTimeHandle;
};
