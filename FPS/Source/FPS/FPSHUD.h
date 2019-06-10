// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

UCLASS()
class AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	TSubclassOf<class UUserWidget> CrosshairWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Crosshair")
	class UUserWidget* CrosshairWidget;

};

