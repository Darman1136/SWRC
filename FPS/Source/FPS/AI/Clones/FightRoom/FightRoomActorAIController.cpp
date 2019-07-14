// Fill out your copyright notice in the Description page of Project Settings.

#include "FightRoomActorAIController.h"
#include "FightRoomActorAICharacter.h"

void AFightRoomActorAIController::BeginPlay() {
	Super::BeginPlay();

}

void AFightRoomActorAIController::StartBehaviorTree() {
	Super::StartBehaviorTree();

	AActor* Pawn = GetPawn();
	if (BehaviorTree && Pawn && Pawn->IsA(AFightRoomActorAICharacter::StaticClass())) {
		AFightRoomActorAICharacter* Character = Cast<AFightRoomActorAICharacter>(Pawn);

		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		if (BlackboardComponent != nullptr) {
			BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, Character->GetAimTarget());
		}
	}
}
