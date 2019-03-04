// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageAreaEnum.generated.h"

UENUM(BlueprintType)
enum class EDamageArea : uint8
{
	DADefault,
	DAHead,
	DABody,
	DALeftArm,
	DARightArm,
	DALeftLeg,
	DARightLeg
};
