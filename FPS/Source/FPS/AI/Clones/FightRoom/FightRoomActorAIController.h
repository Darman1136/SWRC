// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Clones/StaticActorAIController.h"
#include "FightRoomActorAIController.generated.h"

/**
 *
 */
UCLASS()
class FPS_API AFightRoomActorAIController : public AStaticActorAIController {
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		FName TargetBlackboardKeyName;
};
