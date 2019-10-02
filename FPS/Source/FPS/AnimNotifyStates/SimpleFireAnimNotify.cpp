


#include "SimpleFireAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "AI/BasicAICharacter.h"
#include "AI/BasicAIController.h"

void USimpleFireAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	AActor* CurrentActor = MeshComp->GetOwner();
	if (CurrentActor && CurrentActor->IsA(ABasicAICharacter::StaticClass())) {
		Cast<ABasicAICharacter>(CurrentActor)->FireProjectile(true);
	}
}
