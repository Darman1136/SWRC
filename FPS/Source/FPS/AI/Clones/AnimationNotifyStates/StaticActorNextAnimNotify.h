// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "StaticActorNextAnimNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Play Next Animation StaticActor"))
class FPS_API UStaticActorNextAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
