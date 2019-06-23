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
class FPS_API ABattledroidAIController : public ABasicAIController
{
	GENERATED_BODY()

public:
	ABattledroidAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void TakeDamage(AActor* AttackingActor, EWeaponDamageType DamageType, float amount, const FHitResult& Hit) override;

protected:
	virtual EDamageArea GetTakenDamageAreaByBoneName(FName Bone) override;

	virtual float GetTakenDamageMultiplier(FName Bone) override;

	virtual void OnDeath() override;

private:
	class UBattledroidAnimInstance* BattledroidAnimInstance;

	class UCharacterMovementComponent* CharacterMovementComponent;

	class UBattleDroidStats* BattleDroidStats;

	bool DeathByHeadshot;

	static const float FreakOutByHeadshotChance;

	static const FName BoneNameHead;
};
