// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BattledroidAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class FPS_API UBattledroidAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBattledroidAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		bool InAction = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		bool Alive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		bool DeathByHeadshot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		bool IsFiring = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool IsWalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool TurnRight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool TurnLeft = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float WalkSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool IsRunning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float RunSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		bool IsStrafing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float StrafeSpeed = 0.f;

protected:
	// Returns rotation
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Look")
		void FindLookAtObjectRotator(FRotator& Rotation, float& Alpha);

};

