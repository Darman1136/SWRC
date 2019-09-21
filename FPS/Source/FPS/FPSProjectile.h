// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Projectile/WeaponDamageType.h"
#include "FPSProjectile.generated.h"

UCLASS(config = Game)
class AFPSProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFPSProjectile();

	virtual void BeginPlay() override;

	/** called when projectile hits something */
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	EWeaponDamageType GetDamageType();

	void SetDamageType(EWeaponDamageType DamageType);

	float GetDamage();

	void SetDamage(float Damage);

protected:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = Impact)
		class UParticleSystem* ImpactGenericParticleSystem;

private:
	UPROPERTY(VisibleAnywhere)
		AActor* ProjectileOwner;

	UPROPERTY(VisibleAnywhere)
		EWeaponDamageType DamageType;

	UPROPERTY(VisibleAnywhere)
		float Damage;
};

