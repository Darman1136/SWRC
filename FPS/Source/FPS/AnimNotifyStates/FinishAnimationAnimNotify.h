

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FinishAnimationAnimNotify.generated.h"

/**
 * 
 */
UCLASS(abstract, meta = (DisplayName = "Abstract Finish Animation"))
class FPS_API UFinishAnimationAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	virtual void DoFinishAnimation(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, AActor* Owner);
};
