


#include "FinishMeleeAnimNotify.h"
#include "FPSCharacter.h"

void UFinishMeleeAnimNotify::DoFinishAnimation(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, AActor* Owner) {
	if (Owner->IsA(AFPSCharacter::StaticClass())) {
		AFPSCharacter* CurrentCharacter = Cast<AFPSCharacter>(Owner);
		CurrentCharacter->FinishPlayerMeshMeleeAnimation();
	}
}
