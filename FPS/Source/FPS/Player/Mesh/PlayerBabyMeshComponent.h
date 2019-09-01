

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
};
