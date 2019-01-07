// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "PrologueCharacter.generated.h"

/**
 *
 */
UCLASS(config = Game)
class FPS_API APrologueCharacter : public AFPSCharacter
{
	GENERATED_BODY()


public:
	APrologueCharacter();

	void OnFire() override;

	void OnReload() override;


};
