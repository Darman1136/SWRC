// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/UseableWeapon.h"
#include "DC17mBlaster.generated.h"


UCLASS(ClassGroup = (Weapon), meta = (BlueprintSpawnableComponent))
class FPS_API UDC17mBlaster : public UObject, public IUseableWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDC17mBlaster();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gun")
		int32 GetDamage();
	virtual int32 GetDamage_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gun")
		int32 GetMaxAmmo();
	virtual int32 GetMaxAmmo_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Gun")
		int32 GetMagSize();
	virtual int32 GetMagSize_Implementation() override;

private:
	FWeaponDataTable* BlasterStats;
};
