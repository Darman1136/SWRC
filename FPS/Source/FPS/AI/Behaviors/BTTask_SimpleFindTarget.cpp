


#include "BTTask_SimpleFindTarget.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AI/BasicAIController.h"
#include "Player/PlayerCharacter.h"

UBTTask_SimpleFindTarget::UBTTask_SimpleFindTarget() : Super() {
	NodeName = "Look At Actor";
}

EBTNodeResult::Type UBTTask_SimpleFindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AActor* Owner = OwnerComp.GetOwner();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0) {
		UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
		BlackboardComponent->SetValueAsObject(BlackboardKey.SelectedKeyName, FoundActors[0]);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

FString UBTTask_SimpleFindTarget::GetStaticDescription() const {
	return FString::Printf(TEXT("%s: %s"), *FString("Current Target"), *BlackboardKey.SelectedKeyName.ToString());
}