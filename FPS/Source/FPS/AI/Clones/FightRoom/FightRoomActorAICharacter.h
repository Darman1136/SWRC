// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Clones/StaticActorAICharacter.h"
#include "FightRoomActorAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AFightRoomActorAICharacter : public AStaticActorAICharacter
{
	GENERATED_BODY()
	
public:
	AActor* GetAimTarget();

private:
	UPROPERTY(EditAnywhere)
		AActor* AimTarget;
};
