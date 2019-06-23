// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Strafe.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "AI/BasicAIController.h"

UBTTask_Strafe::UBTTask_Strafe() : Super()
{
	NodeName = "Strafe To";
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Strafe::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	AActor* Owner = OwnerComp.GetOwner();
	if (Owner && Owner->IsA(ABasicAIController::StaticClass())) {
		ABasicAIController* Controller = Cast<ABasicAIController>(Owner);

		FVector Direction = Controller->GetPawn()->GetActorRightVector();
		if (FMath::RandBool()) {
			Direction = -Direction;
		}


		FVector Destination = Direction * MaxStrafeDistance;

		DrawDebugSphere(GetWorld(), Destination, 20.f, 10, FColor(255, 0, 0), false, 5.f, 0, 5.f);

		UNavigationSystemBase* NavigationSystemBase = GetWorld()->GetNavigationSystem();
		if (NavigationSystemBase && NavigationSystemBase->IsA(UNavigationSystemV1::StaticClass())) {
			UNavigationSystemV1* NavigationSystem = Cast<UNavigationSystemV1>(NavigationSystemBase);

			FNavLocation ActualNavLocation;
			NavigationSystem->ProjectPointToNavigation(Destination, ActualNavLocation);
			FVector ActualDestination = ActualNavLocation.Location;

			DrawDebugSphere(GetWorld(), ActualDestination, 20.f, 10, FColor(255, 0, 255), false, 5.f, 0, 5.f);

			UE_LOG(LogTemp, Warning, TEXT("MoveTo"));
			EPathFollowingRequestResult::Type RequestResult = Controller->MoveToLocation(ActualDestination, 200.f);

			//if (RequestResult == EPathFollowingRequestResult::RequestSuccessful)
			//{
			//	MyMemory->MoveRequestID = RequestResult.MoveId;
			//	WaitForMessage(OwnerComp, UBrainComponent::AIMessage_MoveFinished, RequestResult.MoveId);
			//	WaitForMessage(OwnerComp, UBrainComponent::AIMessage_RepathFailed);

			//	NodeResult = EBTNodeResult::InProgress;
			//}
			//else if (RequestResult == EPathFollowingRequestResult::AlreadyAtGoal)
			//{
			//	NodeResult = EBTNodeResult::Succeeded;
			//}

			return NodeResult;
		}
	}
	return EBTNodeResult::Failed;
}


