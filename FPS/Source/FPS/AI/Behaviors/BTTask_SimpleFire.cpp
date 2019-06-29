// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SimpleFire.h"
#include "AI/BasicAIController.h"
#include "AI/BasicAICharacter.h"


UBTTask_SimpleFire::UBTTask_SimpleFire() : Super() {
	NodeName = "Simple Fire";
	Repeats = 1;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SimpleFire::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) {
	AActor* Owner = OwnerComp.GetOwner();
	if (Owner->IsA(ABasicAIController::StaticClass())) {
		TriggerFire(Owner);

		FBTSimpleFireTaskMemory* MyMemory = (FBTSimpleFireTaskMemory*)NodeMemory;
		MyMemory->DoneRepeats = 1;
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UBTTask_SimpleFire::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	AActor* Owner = OwnerComp.GetOwner();
	FBTSimpleFireTaskMemory* MyMemory = (FBTSimpleFireTaskMemory*)NodeMemory;

	ABasicAIController* Controller = Cast<ABasicAIController>(Owner);
	ABasicAICharacter* Character = Cast<ABasicAICharacter>(Controller->GetPawn());

	if (Character->IsReadyToFire()) {
		MyMemory->DoneRepeats += 1;
		if (IsTaskDone(Owner, MyMemory)) {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		} else {
			TriggerFire(Owner);
		}
	}
}

bool UBTTask_SimpleFire::IsTaskDone(AActor* Owner, FBTSimpleFireTaskMemory* MyMemory) {
	// UE_LOG(LogTemp, Warning, TEXT("Reps: %d - %s"), MyMemory->DoneRepeats, *Owner->GetName());
	return MyMemory->DoneRepeats >= Repeats;
}

void UBTTask_SimpleFire::TriggerFire(AActor* Owner) {
	ABasicAIController* Controller = Cast<ABasicAIController>(Owner);
	ABasicAICharacter* Character = Cast<ABasicAICharacter>(Controller->GetPawn());
	if (Character->IsReadyToFire()) {
		Character->OnFire();
	}
}

FString UBTTask_SimpleFire::GetStaticDescription() const {
	return FString::Printf(TEXT("%s x%d"), *FString("Simple fire"), Repeats);
}

