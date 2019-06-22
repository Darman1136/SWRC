// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Clones/CloneAICharacter.h"
#include "FightRoomActorAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFightRoomActorAICharacter : public ACloneAICharacter
{
	GENERATED_BODY()
	
public:
	// AFightRoomActorAICharacter();

	AActor* GetAimTarget();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		AActor* AimTarget;
};
