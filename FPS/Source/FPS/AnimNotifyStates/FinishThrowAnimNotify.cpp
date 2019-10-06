


#include "FinishThrowAnimNotify.h"
#include "FPSCharacter.h"

void UFinishThrowAnimNotify::DoFinishAnimation(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, AActor* Owner) {
	if (Owner->IsA(AFPSCharacter::StaticClass())) {
		AFPSCharacter* CurrentCharacter = Cast<AFPSCharacter>(Owner);
		CurrentCharacter->FinishPlayerMeshThrowAnimation();
	}
}
