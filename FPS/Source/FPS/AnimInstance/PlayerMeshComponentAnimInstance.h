

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float MovementSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsFiring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsHolstering = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsLoading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsZooming = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsMeleeing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsThrowingNade = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		bool IsSwitchingDC17Attachments = false;
};
