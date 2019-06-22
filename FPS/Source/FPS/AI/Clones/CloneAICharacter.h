// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BasicAICharacter.h"
#include "CloneAICharacter.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ACloneAICharacter : public ABasicAICharacter {
	GENERATED_BODY()

public:
	ACloneAICharacter();

	virtual void OnFire() override;

	class UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	class USphereComponent* GetMuzzle() const { return Muzzle; }

	virtual bool IsReadyToFire() override;

protected:
	virtual void BeginPlay() override;

	virtual bool IsMagEmpty();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USphereComponent* Muzzle;

	/* Shot accuracy, 0 = bad, 1 = perfect */
	UPROPERTY(EditAnywhere, Category = Gun, meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float Accuracy = 1.f;

	UPROPERTY(EditAnywhere, Category = Gun)
		float MaxAccuracyDeviation = 10.f;

private:
	float GetRandomDeviation(float MaxDeviation);

private:
	bool bIsFiring = false;

	UPROPERTY(EditAnywhere, Category = Gun)
		int32 CurrentAmmo = 30;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	class UWeaponStats* WeaponStats;
};
