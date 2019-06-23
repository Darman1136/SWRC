// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyStats.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Data/EnemyStats/EnemyDataTable.h"

UEnemyStats::UEnemyStats() : Super() {
	ConstructorHelpers::FObjectFinder<UDataTable>
		Data_BP(TEXT("DataTable'/Game/Data/EnemyData.EnemyData'"));
	Data = Data_BP.Object;
}

int32 UEnemyStats::GetMaxHealth()
{
	if (EnemyData) {
		return EnemyData->MaxHealth;
	}
	return 0;
}

int32 UEnemyStats::GetHealth()
{
	if (EnemyData) {
		return EnemyData->Health;
	}
	return 0;
}

float UEnemyStats::GetWalkSpeed()
{
	if (EnemyData) {
		return EnemyData->WalkSpeed;
	}
	return 0.0f;
}

float UEnemyStats::GetCrouchSpeed()
{
	if (EnemyData) {
		return EnemyData->CrouchSpeed;
	}
	return 0.0f;
}
