

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerMeshComponentAnimInstance.generated.h"

/**
 * 
 */
UCLASS(abstract)
class FPS_API UPlayerMeshComponentAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerMeshComponentAnimInstance();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float MovementSpeed = 0.f;
};
