// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Weapon/Projectile/WeaponDamageType.h"
#include "Weapon/Projectile/DamageAreaEnum.h"
#include "BasicAIController.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ABasicAIController : public AAIController {
	GENERATED_BODY()

public:
	ABasicAIController();

	virtual void OnPossess(class APawn* InPawn) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	int32 GetHealth();

	virtual void TakeDamage(AActor* AttackingActor, EWeaponDamageType DamageType, float amount, const FHitResult& Hit);

	virtual void LookedAtByPlayer(AActor* PlayerActor);

	virtual void StartBehaviorTree();

protected:
	virtual void TurnHeadToObject(AActor* Actor);

	virtual EDamageArea GetTakenDamageAreaByBoneName(FName Bone);

	virtual float GetTakenDamageMultiplier(FName Bone);

	virtual void OnDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = AI)
		class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = AIProperties)
		int MaxHealth = 100;
	UPROPERTY(EditAnywhere, Category = AIProperties)
		int Health = 100;

	UPROPERTY(EditAnywhere, Category = Animation)
		bool LookAtCanInterrupt = false;

	UPROPERTY(EditAnywhere, Category = AIProperties)
		bool AutoStartBehaviorTree = false;

private:
	void InitializeBlackboardWithValues();

public:
	static const FName BKTarget;
	static const FName BKTargetLocation;

};

