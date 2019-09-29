


#include "FinishAnimationAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"

void UFinishAnimationAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) {
	AActor* Actor = MeshComp->GetOwner();
	if (Actor) {
		DoFinishAnimation(MeshComp, Animation, Actor);
	}
}

void UFinishAnimationAnimNotify::DoFinishAnimation(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, AActor* Owner) {}
