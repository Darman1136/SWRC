// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoverTriggerBox.h"
#include "MoverLerpActor.generated.h"

UCLASS()
class FPS_API AMoverLerpActor : public AActor {
	GENERATED_BODY()

public:
	AMoverLerpActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Mover)
	void TriggerMover(bool MovesOnCollisionTriggerAfterwards = true);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* MoverMesh;

private:
	void InitializeValues();

	void InitializeTriggers();

	void PauseBeforeReverse(float Delay);

	void TriggerReverse();

	bool CanStartReverse();

	void Finished();

	UFUNCTION()
		void AddActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void RemoveActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	// Translation
	void DoTranslation(float LerpAlpha);

	void TranslateForwards(float LerpAlpha);

	void TranslateBackwards(float LerpAlpha);

	void Translate(FVector StartLocation, FVector EndLocation, float LerpAlpha);

	// Rotation
	void DoRotation(float LerpAlpha);

	void RotateForwards(float LerpAlpha);

	void RotateBackwards(float LerpAlpha);

	void Rotate(FRotator StartRotation, FRotator EndRotation, float LerpAlpha);

private:

	// Settings
	UPROPERTY(EditAnywhere, Category = MoverSettings)
		bool AlwaysOn = false;

	UPROPERTY(VisibleAnywhere, Category = MoverSettings)
		bool Triggered = false;

	/* Time to lerp from start to end position in ms */
	UPROPERTY(EditAnywhere, Category = MoverSettings, meta = (ClampMin = "0.0"))
		float EndMovementDelay = 1000.f;


	UPROPERTY(EditAnywhere, Category = MoverSettings)
		bool EnableReverse = false;

	/* In ms */
	UPROPERTY(EditAnywhere, Category = MoverSettings, meta = (ClampMin = "0.0", EditCondition = "EnableReverse"))
		float DelayBeforeReverse = 1000.f;

	FTimerHandle ReverseTimerHandle;

	UPROPERTY(EditAnywhere, Category = MoverSettingsTrigger)
		bool TriggersStartMover = false;

	/* Triggers the mover. Also before mover starts it's reverse animation, these must not collide with actor classes specified */
	UPROPERTY(EditAnywhere, Category = MoverSettingsTrigger)
		TArray<AMoverTriggerBox*> TriggerColliders;

	/* The actors the colliders care about */
	UPROPERTY(EditAnywhere, Category = MoverSettingsTrigger)
		TArray<UClass*> TriggerCollidersImportantActors;

	/* Array which holds the actors currently blocking the reverse animation */
	TArray<AActor*> BlockingActors;

	FVector InitialTranslation;
	FRotator InitialRotation;

	bool Paused = false;

	float TimeSinceMovementStart = 0.f;

	bool ReverseActive = false;

	bool Done = false;

	// Translation
	UPROPERTY(EditAnywhere, Category = MoverTranslation)
		bool EnableTranslation = false;

	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (EditCondition = "EnableTranslation"))
		FVector RelativeTranslation;

	FVector EndTranslation;

	// Rotation
	UPROPERTY(EditAnywhere, Category = MoverRotation)
		bool EnableRotation = false;

	UPROPERTY(EditAnywhere, Category = MoverRotation, meta = (EditCondition = "EnableRotation"))
		FRotator RelativeRotation;

	FRotator EndRotation;

};
