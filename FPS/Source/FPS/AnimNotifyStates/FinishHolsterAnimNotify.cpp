


#include "FinishHolsterAnimNotify.h"
#include "FPSCharacter.h"

void UFinishHolsterAnimNotify::DoFinishAnimation(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, AActor* Owner) {
	if (Owner->IsA(AFPSCharacter::StaticClass())) {
		AFPSCharacter* CurrentCharacter = Cast<AFPSCharacter>(Owner);
		CurrentCharacter->FinishPlayerMeshHolsterAnimation();
	}
}