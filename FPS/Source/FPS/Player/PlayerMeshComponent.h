

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
	bool ActivatePlayerMesh();
	/* True if an animation was set to play, false if none available */
	bool DeactivatePlayerMesh();

	UFUNCTION(BlueprintCallable)
		virtual void TriggerMainAction();

	virtual void TriggerStopMainAction();

	FORCEINLINE EPlayerMeshType GetPlayerMeshType() const { return PlayerMeshType; }

	FORCEINLINE bool IsVisiorEnabled() const { return VisiorEnabled; }

	virtual void FinishLoadAnimation();

	virtual void FinishHolsterAnimation();

protected:
	virtual void BeginPlay() override;

	virtual void DoMainAction();

	virtual void DoStopMainAction();

	virtual bool ShowLoadAnimation();

	virtual bool ShowHolsterAnimation();

protected:
	EPlayerMeshType PlayerMeshType;

	bool VisiorEnabled = true;

	AActor* Parent;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* MainActionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* HolsterAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
		class UAnimMontage* LoadAnimation;

	UCameraComponent* Camera;
};
