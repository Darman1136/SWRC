// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAIController.h"
#include "Animation/AnimationAsset.h"
#include "StaticActorAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API AStaticActorAIController : public ABasicAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void StartAnimationCycle();
	
	void PlayNextAnimation();

protected:
	TMap<int32, UAnimSequence *> AnimationCycle;

private:
	bool loop = true;
};
