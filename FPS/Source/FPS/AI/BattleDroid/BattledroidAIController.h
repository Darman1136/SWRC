// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAIController.h"
#include "BattledroidAIController.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ABattledroidAIController : public ABasicAIController
{
	GENERATED_BODY()

public:
	ABattledroidAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	class UBattledroidAnimInstance* BattledroidAnimInstance;

	class UCharacterMovementComponent* CharacterMovementComponent;
};
