// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MoverTriggerBox.generated.h"

/**
 * This Trigger is used to check if a Mover is able to start playing it's reverse animation. No Actors of the given type should be inside.
 */
UCLASS()
class FPS_API AMoverTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	
};
