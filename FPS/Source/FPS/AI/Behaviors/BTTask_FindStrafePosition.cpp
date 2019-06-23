// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindStrafePosition.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "AI/BasicAIController.h"

UBTTask_FindStrafePosition::UBTTask_FindStrafePosition() : Super() {
	NodeName = "Find Strafe To Position";
}

EBTNodeResult::Type UBTTask_FindStrafePosition::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AActor* Owner = OwnerComp.GetOwner();
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (Owner && Owner->IsA(ABasicAIController::StaticClass()) && BlackboardComponent) {
		ABasicAIController* Controller = Cast<ABasicAIController>(Owner);

		APawn* Pawn = Controller->GetPawn();
		FVector Direction = Pawn->GetActorRightVector();
		//if (FMath::RandBool()) {
			Direction = -Direction;
		//}
		FVector Destination = Pawn->GetActorLocation() + Direction * MaxStrafeDistance;

		UNavigationSystemBase* NavigationSystemBase = GetWorld()->GetNavigationSystem();
		if (NavigationSystemBase && NavigationSystemBase->IsA(UNavigationSystemV1::StaticClass())) {
			UNavigationSystemV1* NavigationSystem = Cast<UNavigationSystemV1>(NavigationSystemBase);

			FNavLocation ActualNavLocation;
			NavigationSystem->ProjectPointToNavigation(Destination, ActualNavLocation);
			FVector ActualDestination = ActualNavLocation.Location;

			DrawDebugSphere(GetWorld(), ActualDestination, 20.f, 10, FColor(255, 0, 255), false, 5.f, 0, 5.f);

			BlackboardComponent->SetValueAsVector(BKStrafeLocation, ActualDestination);

			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
