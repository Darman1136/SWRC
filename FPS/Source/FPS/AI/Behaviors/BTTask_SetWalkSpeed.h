// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetWalkSpeed.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_SetWalkSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_SetWalkSpeed();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual FString GetStaticDescription() const override;
public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "10.", UIMin = "10."))
		float SpeedToSet = 150.f;
};
