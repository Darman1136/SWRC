// Fill out your copyright notice in the Description page of Project Settings.

#include "FightRoomActorAIController.h"
#include "FightRoomActorAICharacter.h"



void AFightRoomActorAIController::BeginPlay() {
	Super::BeginPlay();

	AActor* Pawn = GetPawn();
	if (BehaviorTree && Pawn && Pawn->IsA(AFightRoomActorAICharacter::StaticClass())) {
		AFightRoomActorAICharacter* Character = Cast<AFightRoomActorAICharacter>(Pawn);

		UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, Character->GetAimTarget());

		RunBehaviorTree(BehaviorTree);
	}
}
