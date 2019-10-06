


#include "SimpleThrowAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSCharacter.h"

void USimpleThrowAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	AActor* CurrentActor = MeshComp->GetOwner();
	if (CurrentActor && CurrentActor->IsA(AFPSCharacter::StaticClass())) {
		Cast<AFPSCharacter>(CurrentActor)->DoThrow();
	}
}
