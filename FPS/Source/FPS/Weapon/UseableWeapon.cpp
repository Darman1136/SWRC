// Fill out your copyright notice in the Description page of Project Settings.

#include "UseableWeapon.h"
#include "Engine/DataTable.h"
#include "Data/WeaponDataTable.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

UUseableWeapon::UUseableWeapon() : Super() {

}

IUseableWeapon::IUseableWeapon() {
	// why does this code sometimes cause exceptions on hot reload
	//ConstructorHelpers::FObjectFinder<UDataTable>
	//	Data_BP(TEXT("DataTable'/Game/Data/WeaponData.WeaponData'"));
	//Data = Data_BP.Object;
}

int32 IUseableWeapon::GetDamageInternal(FWeaponDataTable* WeaponDataTable) {
	if (WeaponDataTable) {
		return WeaponDataTable->Damage;
	}
	return 0;
}

int32 IUseableWeapon::GetMaxAmmoInternal(FWeaponDataTable* WeaponDataTable) {
	if (WeaponDataTable) {
		return WeaponDataTable->MaxAmmo;
	}
	return 0;
}

int32 IUseableWeapon::GetMagSizeInternal(FWeaponDataTable* WeaponDataTable) {
	if (WeaponDataTable) {
		return WeaponDataTable->MagSize;
	}
	return 0;
}
