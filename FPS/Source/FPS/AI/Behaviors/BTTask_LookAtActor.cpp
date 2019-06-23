// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_LookAtActor.h"
#include "AI/BasicAIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"


UBTTask_LookAtActor::UBTTask_LookAtActor() : Super() {
	NodeName = "Look At Actor";
}

EBTNodeResult::Type UBTTask_LookAtActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) {
	AActor* Owner = OwnerComp.GetOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	UObject* Target = BlackboardComponent->GetValueAsObject(TargetBlackboardKeyName);
	if (Target && Target->IsA(AActor::StaticClass())) {
		AActor* TargetActor = Cast<AActor>(Target);
		ABasicAIController* Controller = Cast<ABasicAIController>(Owner);
		Controller->SetFocus(TargetActor);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

FString UBTTask_LookAtActor::GetStaticDescription() const {
	return FString::Printf(TEXT("%s: %s"), *FString("Look at target"), *TargetBlackboardKeyName.ToString());
}

