// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAIController.h"
#include "Weapon/Projectile/DamageAreaEnum.h"
#include "BattledroidAIController.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ABattledroidAIController : public ABasicAIController {
	GENERATED_BODY()

public:
	ABattledroidAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void TakeDamageAI(AActor* AttackingActor, EWeaponDamageType DamageType, float amount, const FHitResult& Hit) override;

public:
	static const FName BKHeadBone1;
	static const FName BKHeadBone2;

protected:
	virtual void OnDeath(FName Bone) override;

	virtual void Dismember(FName Bone, UStaticMesh* MeshToSpawn) override;

protected:
	UPROPERTY(EditAnywhere)
		float FreakOutByHeadshotChance = 0.07f;

private:
	class UBattledroidAnimInstance* BattledroidAnimInstance;

	class UCharacterMovementComponent* CharacterMovementComponent;

	class UBattleDroidStats* BattleDroidStats;

	
};
