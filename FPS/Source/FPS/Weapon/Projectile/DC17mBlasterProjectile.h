// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProjectile.h"
#include "DC17mBlasterProjectile.generated.h"

/**
 *
 */
UCLASS()
class FPS_API ADC17mBlasterProjectile : public AFPSProjectile
{
	GENERATED_BODY()

public:
	ADC17mBlasterProjectile();

	//virtual void BeginPlay();
	virtual void OnConstruction(const FTransform& Transform);

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
