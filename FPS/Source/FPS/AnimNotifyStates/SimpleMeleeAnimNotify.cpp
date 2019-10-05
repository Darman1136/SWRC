


#include "SimpleMeleeAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Player/PlayerCharacter.h"

void USimpleMeleeAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	AActor* CurrentActor = MeshComp->GetOwner();
	if (CurrentActor && CurrentActor->IsA(APlayerCharacter::StaticClass())) {
		Cast<APlayerCharacter>(CurrentActor)->CheckMeleeHit();
	}
}
