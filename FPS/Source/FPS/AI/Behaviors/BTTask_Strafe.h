// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Strafe.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UBTTask_Strafe : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_Strafe(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
		float MaxStrafeDistance;

};
