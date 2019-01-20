// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponStats.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Data/WeaponDataTable.h"

UWeaponStats::UWeaponStats()
{
	ConstructorHelpers::FObjectFinder<UDataTable>
		Data_BP(TEXT("DataTable'/Game/Data/WeaponData.WeaponData'"));
	Data = Data_BP.Object;
}

int32 UWeaponStats::GetDamage()
{
	if (WeaponData)
	{
		return WeaponData->Damage;
	}
	return 0;
}

int32 UWeaponStats::GetMaxAmmo()
{
	if (WeaponData)
	{
		return WeaponData->MaxAmmo;
	}
	return 0;
}

int32 UWeaponStats::GetMagSize()
{
	if (WeaponData)
	{
		return WeaponData->MagSize;
	}
	return 0;
}

bool UWeaponStats::isAOE()
{
	if (WeaponData)
	{
		return WeaponData->AOE;
	}
	return 0;
}

int32 UWeaponStats::GetAOERange()
{
	if (WeaponData)
	{
		return WeaponData->AOERange;
	}
	return 0;
}
