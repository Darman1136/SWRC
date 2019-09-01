

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerMeshComponent.h"
#include "PlayerAnimatedMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UPlayerAnimatedMeshComponent : public UPlayerMeshComponent
{
	GENERATED_BODY()

public:
	UPlayerAnimatedMeshComponent();

	UFUNCTION(BlueprintCallable)
		void TriggerAnimation();

protected:
	virtual void DoAnimation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* AnimationMontage;
};
