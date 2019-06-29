// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoverTriggerBox.h"
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

	virtual bool CanStartReverse();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* MoverMesh;

private:
	void Move(float DeltaTime);

	void PauseBeforeReverse(float Delay);

	void Reverse();

	void DoTranslation(FVector LocalVectorToAdd);

	UFUNCTION()
		void AddActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void RemoveActorInsideCollider(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

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

	/* Before this mover starts it's reverse animation, these must not collide with actors of the given classes */
	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (EditCondition = "ReversableTranslation"))
		TArray<AMoverTriggerBox*> ReverseColliders;

	/* The actors the colliders care about */
	UPROPERTY(EditAnywhere, Category = MoverTranslation, meta = (EditCondition = "ReversableTranslation"))
		TArray<UClass*> ReverseCollidersImportantActors;

	/* Array which holds the actors currently blocking the reverse animation */
	TArray<AActor*> ReverseBlockingActors;

	// Rotation
	UPROPERTY(EditAnywhere, Category = MoverRotation)
		bool EnableRotation = false;

	/* Corresponds to the Axis used for translation aswell. See coordinate system bottom right of viewport. */
	UPROPERTY(EditAnywhere, Category = MoverRotation, meta = (EditCondition = "EnableRotation"))
		FVector Rotation;

	// Inital Params
	FTransform InitialTransform;
};
