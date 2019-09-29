

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyStates/FinishAnimationAnimNotify.h"
#include "FinishHolsterAnimNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Finish Holster Animation"))
class FPS_API UFinishHolsterAnimNotify : public UFinishAnimationAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void DoFinishAnimation(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, AActor* Owner) override;
};
