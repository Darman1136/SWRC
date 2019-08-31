

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerMeshComponent.h"
#include "PlayerBoyMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UPlayerBoyMeshComponent : public UPlayerMeshComponent
{
	GENERATED_BODY()

public:
	UPlayerBoyMeshComponent();

	virtual void Initialize(AActor* CurrentParent) override;
};
