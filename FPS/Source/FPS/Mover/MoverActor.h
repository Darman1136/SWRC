// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoverActor.generated.h"

UCLASS()
class FPS_API AMoverActor : public AActor {
	GENERATED_BODY()

public:
	AMoverActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Mover)
		virtual void TriggerMover();

protected:
	virtual void BeginPlay() override;

	virtual void Translate(float DeltaTime);

	virtual void Rotate(float DeltaTime);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* MoverMesh;

private:
	void Move(float DeltaTime);

	void PauseBeforeReverse();

	void Reverse();

	void DoTranslation(FVector LocalVectorToAdd);

private:
	// Settings
	UPROPERTY(EditAnywhere, Category = MoverSettings)
		bool AlwaysOn = false;

	UPROPERTY(VisibleAnywhere, Category = MoverSettings)
		bool Triggered = false;

	bool Paused = false;

	bool DoneMoveOnce = false;

	// Translation
	UPROPERTY(EditAnywhere, Category = MoverTranslation)
		bool EnableTranslation = false;

	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (EditCondition = "EnableTranslation"))
		FVector Translation;

	/* Only limits the x-axis */
	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (EditCondition = "EnableTranslation"))
		bool LimitTranslation = false;

	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (ClampMin = "0.0", EditCondition = "LimitTranslation"))
		float MaxTranslation = 0.f;

	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (EditCondition = "LimitTranslation"))
		bool ReversableTranslation = false;

	bool IsReversingTranlation = false;

	/* In ms */
	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (ClampMin = "0.0", EditCondition = "ReversableTranslation"))
		float DelayBeforeReverseTranslation = 1000.f;

	FTimerHandle ReverseTranslationTimerHandle;

	// Rotation
	UPROPERTY(EditAnywhere, Category = MoverRotation)
		bool EnableRotation = false;

	/* Corresponds to the Axis used for translation aswell. See coordinate system bottom right of viewport. */
	UPROPERTY(EditAnywhere, Category = MoverRotation, meta = (EditCondition = "EnableRotation"))
		FVector Rotation;

	// Inital Params
	FTransform InitialTransform;
};
