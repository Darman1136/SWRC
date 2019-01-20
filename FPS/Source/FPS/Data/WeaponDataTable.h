// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "WeaponDataTable.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FPS_API FWeaponDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int32 MagSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		bool AOE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		int32 AOERange;
};
