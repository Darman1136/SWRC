// Fill out your copyright notice in the Description page of Project Settings.

#include "FightRoomActorAIController.h"
#include "FightRoomActorAICharacter.h"

void AFightRoomActorAIController::BeginPlay() {
	Super::BeginPlay();

}

void AFightRoomActorAIController::StartBehaviorTree() {
	Super::StartBehaviorTree();

	AActor* CurrentPawn = GetPawn();
	if (BehaviorTree && CurrentPawn && CurrentPawn->IsA(AFightRoomActorAICharacter::StaticClass())) {
		AFightRoomActorAICharacter* CurrentCharacter = Cast<AFightRoomActorAICharacter>(CurrentPawn);

		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		if (BlackboardComponent != nullptr) {
			BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, CurrentCharacter->GetAimTarget());
		}
	}
}
