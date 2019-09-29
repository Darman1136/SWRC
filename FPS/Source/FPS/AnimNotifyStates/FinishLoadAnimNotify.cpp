


#include "FinishLoadAnimNotify.h"
#include "FPSCharacter.h"
#include "Player/PlayerMeshComponent.h"

void UFinishLoadAnimNotify::DoFinishAnimation(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, AActor* Owner) {
	if (Owner->IsA(AFPSCharacter::StaticClass())) {
		AFPSCharacter* CurrentCharacter = Cast<AFPSCharacter>(Owner);
		CurrentCharacter->FinishPlayerMeshLoadAnimation();
	}
}