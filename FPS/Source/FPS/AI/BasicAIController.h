// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BasicAIController.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ABasicAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABasicAIController();

	virtual void Possess(class APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = AI)
		class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackboardComp;

private:
	FName BKPlayer = FName("Player");
	FName BKTargetLocation = FName("TargetLocation");
};

