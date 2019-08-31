

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
	DC17M
};

/**
 * 
 */
UCLASS()
class FPS_API UPlayerMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	UPlayerMeshComponent();

	virtual void Initialize(AActor* CurrentParent);

	virtual void InitializeBeginPlay();

public:
	void Activate();

	void Deactivate();

	virtual void TriggerMainAction();

	virtual void TriggerStopMainAction();

	FORCEINLINE EPlayerMeshType GetPlayerMeshType() const { return PlayerMeshType; }

	FORCEINLINE bool IsVisiorEnabled() const { return VisiorEnabled; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void DoMainAction();

	virtual void DoStopMainAction();

	virtual void ShowLoadAnimation();

	virtual void ShowHolsterAnimation();

protected:
	EPlayerMeshType PlayerMeshType;

	bool VisiorEnabled = true;

	AActor* Parent;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* MainActionAnimation;

	UCameraComponent* Camera;
};
