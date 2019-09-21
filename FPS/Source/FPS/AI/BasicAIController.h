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

/* Broadcasts on death of this AI */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAIDeath);

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

	virtual void TakeDamageAI(AActor* AttackingActor, EWeaponDamageType DamageType, float amount, const FHitResult& Hit);

	virtual void LookedAtByPlayer(AActor* PlayerActor);

	virtual void StartBehaviorTree();

	UPROPERTY(BlueprintAssignable)
		FAIDeath FAIDeath_OnDeath;

protected:
	virtual void TurnHeadToObject(AActor* Actor);

	virtual float GetTakenDamageMultiplier(FName Bone);

	virtual void OnDeath(FName Bone);

	virtual void Dismember(FName Bone, UStaticMesh* MeshToSpawn);

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
	
	UPROPERTY(EditAnywhere, Category = Dismemberment)
		TMap<FName, FName> HitBoneToSpawnBoneMap;

	UPROPERTY(EditAnywhere, Category = Dismemberment)
		TMap<FName, UStaticMesh*> SpawnBoneToStaticMeshMap;

	/* Chance to dismember and spawn the mesh. 0.f to 1.f */
	UPROPERTY(EditAnywhere, Category = Dismemberment)
		TMap<FName, float> SpawnBoneToSpawnChanceMap;

	UPROPERTY(EditAnywhere, Category = Damage)
		TMap<FName, float> HitBoneToDamageMultiplierMap;
};

