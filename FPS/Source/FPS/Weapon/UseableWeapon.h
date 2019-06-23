// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/WeaponDataTable.h"
#include "UseableWeapon.generated.h"

UINTERFACE(BlueprintType)
class FPS_API UUseableWeapon : public UInterface {
	GENERATED_BODY()

		UUseableWeapon();
};

class FPS_API IUseableWeapon {
	GENERATED_BODY()

public:
	IUseableWeapon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun")
		int32 GetDamage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun")
		int32 GetMaxAmmo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gun")
		int32 GetMagSize();

protected:
	UDataTable* Data;
	FWeaponDataTable* WeaponData;

	int32 GetDamageInternal(FWeaponDataTable* WeaponDataTable);

	int32 GetMaxAmmoInternal(FWeaponDataTable* WeaponDataTable);

	int32 GetMagSizeInternal(FWeaponDataTable* WeaponDataTable);
};

//UCLASS(ClassGroup = (Weapon), meta = (BlueprintSpawnableComponent))
//class FPS_API UUseableWeapon : public UObject
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this component's properties
//	UUseableWeapon();
//
//	virtual int32 GetDamage() const = 0;
//
//protected: 	
//	UDataTable* Data;
//
//	int32 GetDamageInternal(FWeaponDataTable* WeaponDataTable);
//};
