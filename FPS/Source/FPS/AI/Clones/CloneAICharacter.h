// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAICharacter.h"
#include "CloneAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ACloneAICharacter : public ABasicAICharacter
{
	GENERATED_BODY()
	
public:
	ACloneAICharacter();

	virtual void OnFire();

	class UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	class USphereComponent* GetMuzzle() const { return Muzzle; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool IsMagEmpty();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USphereComponent* Muzzle;

private:
	bool bIsFiring = false;

	UPROPERTY(VisibleAnywhere, Category = Gun)
		int CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	class UWeaponStats* WeaponStats;
};
