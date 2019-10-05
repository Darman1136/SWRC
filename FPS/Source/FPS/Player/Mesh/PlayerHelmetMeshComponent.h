

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerAnimatedMeshComponent.h"
#include "PlayerHelmetMeshComponent.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UPlayerHelmetMeshComponent : public UPlayerAnimatedMeshComponent {
	GENERATED_BODY()

public:
	UPlayerHelmetMeshComponent();

protected:
	virtual void DoAnimation() override;

	virtual void ShowHolsterAnimation() override;

	virtual void ShowLoadAnimation() override;
};
