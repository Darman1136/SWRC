// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Clones/StaticActorAICharacter.h"
#include "CloneBoyAICharacter.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ACloneBoyAICharacter : public AStaticActorAICharacter {
	GENERATED_BODY()

public:
	UAnimationAsset* GetLookAtAnimation();

	float GetLookAtAnimationLength();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAnimation)
		UAnimationAsset* LookAtAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAnimation)
		float LookAtAnimationLength;

};
