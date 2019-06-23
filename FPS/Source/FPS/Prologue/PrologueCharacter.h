// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "PrologueCharacter.generated.h"

/**
 *
 */
UCLASS(config = Game)
class FPS_API APrologueCharacter : public AFPSCharacter {
	GENERATED_BODY()


public:
	APrologueCharacter();

	void OnFire() override;

	void OnReload() override;

	UFUNCTION(BlueprintCallable, Category = "Mesh")
		void SwitchToBoyMesh();

	UFUNCTION(BlueprintCallable, Category = "Mesh")
		void SwitchToVisorMesh();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	void SendLookRay();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* VisorMeshBoy;

private:
	APlayerCameraManager* CameraManager;
};
