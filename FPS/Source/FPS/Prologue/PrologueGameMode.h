// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSGameMode.h"
#include "PrologueGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API APrologueGameMode : public AFPSGameMode
{
	GENERATED_BODY()
	
public:
	APrologueGameMode();

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	const FName PlayerStartName = FName("InitialLocation");
};
