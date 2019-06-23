// Fill out your copyright notice in the Description page of Project Settings.

#include "DC17mBlasterStats.h"

UDC17mBlasterStats::UDC17mBlasterStats() : Super() {
	if (Data) {
		WeaponData = Data->FindRow<FWeaponDataTable>(FName("DC17mBlaster"), FString(""));
	}
}


