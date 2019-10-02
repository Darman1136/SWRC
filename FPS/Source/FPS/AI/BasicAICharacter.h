// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BasicCharacter.h"
#include "BasicAIController.h"
#include "BasicAICharacter.generated.h"

UCLASS()
class FPS_API ABasicAICharacter : public ABasicCharacter {
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

	virtual void FireProjectile(bool UseWeaponRotation = false);

	virtual bool IsReadyToFire();

	virtual bool IsMagEmpty();

	TMap<FName, AActor*> GetBlackboardObjectMap() { return BlackboardObjectMap; }

	class UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	class USphereComponent* GetMuzzle() const { return Muzzle; }

	bool IsAutoStartBehaviorTree() const { return AutoStartBehaviorTree; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetFireCooldownComplete();

	virtual void AttachWeaponMeshToBone(FName Bone);

protected:
	FTimerHandle FireTimeHandle;

	bool FireCooldownComplete;

	UPROPERTY(EditAnywhere, Category = Fire)
		float FireCooldownDelay = .1f;

	UPROPERTY(EditAnywhere, Category = "AI|Behavior")
		TMap<FName, AActor*> BlackboardObjectMap;

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

	UPROPERTY(EditAnywhere, Category = Gun)
		FName WeaponMeshAttachBone = FName("weaponAttach_R");

	UPROPERTY(EditAnywhere, Category = AIProperties)
		bool AutoStartBehaviorTree = false;

private:
	float GetRandomDeviation(float MaxDeviation);

private:
	bool bIsFiring = false;

	UPROPERTY(EditAnywhere, Category = Gun)
		int32 CurrentAmmo = 30;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;
};
