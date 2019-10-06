

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyStates/FinishAnimationAnimNotify.h"
#include "FinishThrowAnimNotify.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UFinishThrowAnimNotify : public UFinishAnimationAnimNotify {
	GENERATED_BODY()

protected:
	virtual void DoFinishAnimation(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, AActor* Owner) override;
};
