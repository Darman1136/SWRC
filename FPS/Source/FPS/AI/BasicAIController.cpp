// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

const FName ABasicAIController::BKTarget = FName("Target");
const FName ABasicAIController::BKTargetLocation = FName("TargetLocation");

ABasicAIController::ABasicAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
}

void ABasicAIController::Possess(class APawn* InPawn) {
	Super::Possess(InPawn);
	SetPawn(InPawn);

	if (BehaviorTree) {
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
	}
	UE_LOG(LogTemp, Warning, TEXT("Possess"));
}

void ABasicAIController::BeginPlay() {
	Super::BeginPlay();

	if (BehaviorTree) {
		APawn* Pawn = GetPawn();
		if (BlackboardComp != nullptr) {
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPSCharacter::StaticClass(), FoundActors);

			if (FoundActors.Num() == 1) {
				BlackboardComp->SetValueAsObject(ABasicAIController::BKTarget, FoundActors[0]);
				//SetFocus(FoundActors[0], EAIFocusPriority::Gameplay);
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Failed to find and set player"));
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Running BehaviorTree"));
		RunBehaviorTree(BehaviorTree);
	}
}


void ABasicAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

int32 ABasicAIController::GetHealth()
{
	return Health;
}

void ABasicAIController::TakeDamage(AActor * AttackingActor, UObject * DamageType, int32 amount)
{
	Health -= amount;
	if (Health < 0) {
		Health = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %d"), Health);
}

void ABasicAIController::TurnHeadToObject(AActor* Actor)
{

}
