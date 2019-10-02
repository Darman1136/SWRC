

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SimpleFindTarget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBTTask_SimpleFindTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_SimpleFindTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
