// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "Weapon/UseableWeapon.h"
#include "PlayerCharacter.generated.h"

/**
 *
 */
UCLASS(config = Game)
class FPS_API APlayerCharacter : public AFPSCharacter {
	GENERATED_BODY()

public:
	APlayerCharacter();

	void ReloadAmmoCount();

	void OnReload() override;

public:
	//UPROPERTY(VisibleAnywhere, Category = Gun)
	//	TScriptInterface<UUseableWeapon> WeaponStatsReference;
	//UObject* WeaponStatsObject;
	//IUseableWeapon* WeaponStatsInterface;
	// class UWeaponStats* WeaponStats;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void StartWiper();

	void PlayWiper(float DeltaTime);

	void ResetWiper();

protected:
	UPROPERTY(EditAnywhere, Category = "Mesh|Player|DC17M")
		class UPlayerDC17MMeshComponent* PlayerDC17MMeshComponent;

private:
	UMaterialInstanceDynamic* VisorMaterialInstance;
	float VisorWiperStartTime = -2.f;
	float VisorWiperCurrentTime = VisorWiperStartTime;
	bool VisorWiperActive = false;
};
