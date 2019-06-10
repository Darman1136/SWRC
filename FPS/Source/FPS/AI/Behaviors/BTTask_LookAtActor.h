// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_LookAtActor.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UBTTask_LookAtActor : public UBTTask_BlackboardBase {
	GENERATED_BODY()

public:
	UBTTask_LookAtActor(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

public:
	UPROPERTY(EditAnywhere)
		FName TargetBlackboardKeyName;

};
