// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "WeaponDamageType.generated.h"


UENUM(BlueprintType)
enum class EWeaponDamageType : uint8
{
	WDTDefault	UMETA(DisplayName = "Default"),
	WDTEnergy 	UMETA(DisplayName = "Energy"),
	WDTExplosion 	UMETA(DisplayName = "Explosion"),
	WDTBullet 	UMETA(DisplayName = "Bullet")
};
