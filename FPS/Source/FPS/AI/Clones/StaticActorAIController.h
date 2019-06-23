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
class FPS_API AStaticActorAIController : public ABasicAIController {
	GENERATED_BODY()

public:
	AStaticActorAIController();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "CustomAnimation")
		virtual void StartAnimationCycle();

	/* Adds a random delay before starting the animation cycle, Range in milliseconds */
	UFUNCTION(BlueprintCallable, Category = "CustomAnimation")
		virtual void StartAnimationCycleWithDelay(float MinRandomDelay, float MaxRandomDelay);

	void PlayNextAnimation();

	UFUNCTION(BlueprintCallable, Category = "CustomAnimation")
		void StopAnimationCycle();

private:
	void PlayNextAnimationInternal(UAnimationAsset* Animation);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAnimation)
		TArray<UAnimationAsset*> AnimationCycle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAnimation)
		bool LoopCustomAnimation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAnimation)
		bool AutoStartCustomAnimation = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomAnimation, meta = (ClampMin = "1.0", UIMin = "1.0", EditCondition = "AutoStartCustomAnimation"))
		float AutoStartDelay = 1.f;

private:
	int32 CurrentAnimationIndex = 0;

	FTimerHandle AutoStartTimerHandle;

	bool PlayNext = true;
};
