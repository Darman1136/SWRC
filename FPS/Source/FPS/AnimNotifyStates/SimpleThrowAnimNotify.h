

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SimpleThrowAnimNotify.generated.h"

/**
 *
 */
UCLASS()
class FPS_API USimpleThrowAnimNotify : public UAnimNotify {
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
