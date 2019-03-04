// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/EnemyStats/EnemyStats.h"
#include "BattleDroidStats.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBattleDroidStats : public UEnemyStats
{
	GENERATED_BODY()
	
public:
	UBattleDroidStats(const FObjectInitializer& ObjectInitializer);
	
private:
	const FName BattleDroidEntry = FName("BattleDroid");
};
