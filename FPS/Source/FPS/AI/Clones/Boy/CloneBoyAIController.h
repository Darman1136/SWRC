// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Clones/StaticActorAIController.h"
#include "CloneBoyAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ACloneBoyAIController : public AStaticActorAIController
{
	GENERATED_BODY()
	
public:
	ACloneBoyAIController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void LookedAtByPlayer(AActor* PlayerActor) override;
};
