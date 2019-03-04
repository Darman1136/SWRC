// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/WeaponDataTable.h"
#include "Engine/StaticMesh.h"
#include "Weapon/Projectile/WeaponDamageType.h"
#include "WeaponStats.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UWeaponStats : public UObject
{
	GENERATED_BODY()

public:
	UWeaponStats(const FObjectInitializer& ObjectInitializer);

	TSoftObjectPtr<UStaticMesh> GetMesh();
	EWeaponDamageType GetDamageType();
	int32 GetDamage();
	int32 GetMaxAmmo();
	int32 GetMagSize();
	bool isAOE();
	int32 GetAOERange();


protected:
	UDataTable* Data;
	FWeaponDataTable* WeaponData;

};
