// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAICharacter.h"
#include "CloneAICharacter.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ACloneAICharacter : public ABasicAICharacter {
	GENERATED_BODY()

public:
	ACloneAICharacter();

protected:
	virtual void BeginPlay() override;

	// class UWeaponStats* WeaponStats;
};
