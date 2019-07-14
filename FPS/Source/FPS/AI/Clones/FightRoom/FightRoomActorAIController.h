// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Clones/CloneAIController.h"
#include "FightRoomActorAIController.generated.h"

/**
 *
 */
UCLASS()
class FPS_API AFightRoomActorAIController : public ACloneAIController {
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "AI")
		virtual void StartBehaviorTree() override;

private:
	UPROPERTY(EditAnywhere)
		FName TargetBlackboardKeyName;
};
