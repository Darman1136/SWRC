// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BasicAIController.h"
#include "BasicAICharacter.generated.h"

UCLASS()
class FPS_API ABasicAICharacter : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicAICharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	template <typename ABasicAIController>
	ABasicAIController* GetCastedController() {
		return Cast<ABasicAIController>(GetController());
	}

	virtual void OnFire();

	virtual bool IsReadyToFire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
