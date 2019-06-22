// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SimpleFire.generated.h"

struct FBTSimpleFireTaskMemory {
	int32 DoneRepeats;
};

/**
 *
 */
UCLASS()
class FPS_API UBTTask_SimpleFire : public UBTTask_BlackboardBase {
	GENERATED_BODY()

public:
	UBTTask_SimpleFire(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FBTSimpleFireTaskMemory); }

public:
	UPROPERTY(EditAnywhere)
		int32 Repeats;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	void TriggerFire(AActor* Owner);

	bool IsTaskDone(AActor* Owner, FBTSimpleFireTaskMemory* MyMemory);
};
