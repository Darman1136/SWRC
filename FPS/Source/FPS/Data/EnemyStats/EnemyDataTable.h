// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPS_API FEnemyDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float CrouchSpeed;
};
