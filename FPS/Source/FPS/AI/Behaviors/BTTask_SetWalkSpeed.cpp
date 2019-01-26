// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetWalkSpeed.h"
#include "AI/BasicAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"

UBTTask_SetWalkSpeed::UBTTask_SetWalkSpeed(const FObjectInitializer& ObjectInitializer) {
	NodeName = "Set Walk Speed";
}

EBTNodeResult::Type UBTTask_SetWalkSpeed::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	if (SpeedToSet > 0) {
		AActor* Owner = OwnerComp.GetOwner();
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		if (Owner && Owner->IsA(ABasicAIController::StaticClass())) {
			ABasicAIController* Controller = Cast<ABasicAIController>(Owner);
			UPawnMovementComponent* PawnMovementComponent = Controller->GetPawn()->GetMovementComponent();
			if (PawnMovementComponent && PawnMovementComponent->IsA(UCharacterMovementComponent::StaticClass())) {
				UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(PawnMovementComponent);
				CharacterMovementComponent->MaxWalkSpeed = SpeedToSet;
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}

FString UBTTask_SetWalkSpeed::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %s"), *FString("Set Max WalkSpeed To "), *FString::SanitizeFloat(SpeedToSet));
}