// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "Weapon/UseableWeapon.h"
#include "PlayerCharacter.generated.h"

/**
 *
 */
UCLASS(config = Game)
class FPS_API APlayerCharacter : public AFPSCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	void UpdateAmmoMaterials();

	void ReloadAmmo();

	void OnFire() override;

	void OnReload() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		int MaxAmmo = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
		int MaxMagAmmo = 60;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		int CurrentAmmo;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		int CurrentMagAmmo;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		class UMaterialInstanceDynamic* AmmoDigit100;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		class UMaterialInstanceDynamic* AmmoDigit10;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		class UMaterialInstanceDynamic* AmmoDigit1;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		class UMaterialInstanceDynamic* AmmoChargeMag;

	//UPROPERTY(VisibleAnywhere, Category = Gun)
	//	TScriptInterface<UUseableWeapon> WeaponStatsReference;
	//UObject* WeaponStatsObject;
	//IUseableWeapon* WeaponStatsInterface;
	class UWeaponStats* WeaponStats;

protected:
	virtual void BeginPlay();

	bool isMagEmpty();

private:
	void GetDamage();
};
