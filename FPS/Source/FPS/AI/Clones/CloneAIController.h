// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAIController.h"
#include "CloneAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ACloneAIController : public ABasicAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	
};
