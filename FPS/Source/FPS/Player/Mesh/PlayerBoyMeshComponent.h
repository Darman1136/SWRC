

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

protected:
	virtual void ShowHolsterAnimation() override;

	virtual void ShowLoadAnimation() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* BoyVisorMesh;
};
