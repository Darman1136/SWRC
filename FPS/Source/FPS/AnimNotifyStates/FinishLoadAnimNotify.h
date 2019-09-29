

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyStates/FinishAnimationAnimNotify.h"
#include "FinishLoadAnimNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Finish Load Animation"))
class FPS_API UFinishLoadAnimNotify : public UFinishAnimationAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void DoFinishAnimation(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, AActor* Owner) override;
};
