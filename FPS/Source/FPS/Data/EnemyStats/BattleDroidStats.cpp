// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleDroidStats.h"

UBattleDroidStats::UBattleDroidStats(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	if (Data) {
		EnemyData = Data->FindRow<FEnemyDataTable>(BattleDroidEntry, FString(""));
	}
}



