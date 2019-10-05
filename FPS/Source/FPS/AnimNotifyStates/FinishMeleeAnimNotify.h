

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyStates/FinishAnimationAnimNotify.h"
#include "FinishMeleeAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UFinishMeleeAnimNotify : public UFinishAnimationAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void DoFinishAnimation(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, AActor* Owner) override;
};
