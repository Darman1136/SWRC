// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TurnAIControllerAnimNotify.generated.h"

UENUM(BlueprintType)
enum class ETurnDirection : uint8
{
	TDRight 	UMETA(DisplayName = "Right"),
	TDLeft 	UMETA(DisplayName = "Left")
};

/**
 * 
 */
UCLASS(meta = (DisplayName = "Turn AIController"))
class FPS_API UTurnAIControllerAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		ETurnDirection TurnDirection;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
			float TurnAngle;
};
