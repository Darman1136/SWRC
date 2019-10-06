

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerMeshComponent.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerMeshComponent, Warning, All);

UENUM(BlueprintType)
enum class EPlayerMeshType : uint8 {
	NONE,
	BABY,
	BOY,
	PROLOGUE_HELMET,
	DC17M,
	DC15S
};

/**
 *
 */
UCLASS()
class FPS_API UPlayerMeshComponent : public USkeletalMeshComponent {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UPlayerMeshComponent();

	virtual void Initialize(AActor* CurrentParent);

	virtual void InitializeBeginPlay();

	/* True if an animation was set to play, false if none available */
	void ActivatePlayerMesh();
	/* True if an animation was set to play, false if none available */
	void DeactivatePlayerMesh();

	UFUNCTION(BlueprintCallable)
		virtual void TriggerMainAction();

	virtual void TriggerStopMainAction();

	virtual void TriggerMeleeAction();

	virtual void TriggerThrowAction();

	FORCEINLINE EPlayerMeshType GetPlayerMeshType() const { return PlayerMeshType; }

	FORCEINLINE bool IsVisiorEnabled() const { return VisiorEnabled; }

	bool CanZoom() { return bCanZoom && CanUseZoom(); }

	virtual void FinishLoadAnimation();

	virtual void FinishHolsterAnimation();

	virtual void FinishMeleeAnimation();

	virtual void FinishThrowAnimation();

	virtual void TriggerZoom();

protected:
	virtual void BeginPlay() override;

	virtual void DoMainAction();

	virtual void DoStopMainAction();

	virtual void DoMeleeAction();

	virtual void ShowLoadAnimation();

	virtual void ShowHolsterAnimation();

	virtual bool CanUseMainAction();

	virtual bool CanUseMeleeAction();

	virtual bool CanUseZoom();

	virtual bool CanUseThrow();

	void ShowLoadAnimationMesh();

	virtual void ResetState();

	virtual void DoZoom();

protected:
	EPlayerMeshType PlayerMeshType;

	class AActor* Parent;
	class UCameraComponent* Camera;

	bool VisiorEnabled = true;
	bool bCanZoom = true;

	/* State variables */
	bool bIsActive = false;
	bool bIsLoading = false;
	bool bIsHolstering = false;
	bool bIsMeleeing = false;
	bool bIsThrowing = false;
	/* State variables */

private:
	FTimerHandle ShowLoadMeshHandle;
};
