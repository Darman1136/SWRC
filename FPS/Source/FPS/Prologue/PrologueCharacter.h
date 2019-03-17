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
class FPS_API APrologueCharacter : public AFPSCharacter
{
	GENERATED_BODY()


public:
	APrologueCharacter(const FObjectInitializer& ObjectInitializer);

	void OnFire() override;

	void OnReload() override;

protected:
	virtual void BeginPlay();

private:
	APlayerCameraManager* CameraManager;
};
