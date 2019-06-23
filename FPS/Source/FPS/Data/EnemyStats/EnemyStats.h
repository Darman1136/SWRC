// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EnemyStats/EnemyDataTable.h"
#include "EnemyStats.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UEnemyStats : public UObject
{
	GENERATED_BODY()

public:
	UEnemyStats();

	int32 GetMaxHealth();
	int32 GetHealth();
	float GetWalkSpeed();
	float GetCrouchSpeed();


protected:
	UDataTable* Data;
	FEnemyDataTable* EnemyData;
};