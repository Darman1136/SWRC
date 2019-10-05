

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerMeshComponent.h"
#include "PlayerBabyMeshComponent.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UPlayerBabyMeshComponent : public UPlayerMeshComponent {
	GENERATED_BODY()

public:
	UPlayerBabyMeshComponent();

protected:
	virtual void DoMainAction() override;

	virtual void ShowHolsterAnimation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* MainActionAnimation;
};
