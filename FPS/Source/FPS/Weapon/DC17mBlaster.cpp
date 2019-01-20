// Fill out your copyright notice in the Description page of Project Settings.

#include "DC17mBlaster.h"


// Sets default values for this component's properties
UDC17mBlaster::UDC17mBlaster()
{
	if (Data) {
		BlasterStats = Data->FindRow<FWeaponDataTable>(FName("DC17mBlaster"), FString(""));
	}
}

int32 UDC17mBlaster::GetDamage_Implementation()
{
	return GetDamageInternal(BlasterStats);
}

int32 UDC17mBlaster::GetMaxAmmo_Implementation()
{
	return GetMaxAmmoInternal(BlasterStats);
}

int32 UDC17mBlaster::GetMagSize_Implementation()
{
	return GetMagSizeInternal(BlasterStats);
}
