// Fill out your copyright notice in the Description page of Project Settings.

#include "PrologueGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "FPSHUD.h"

APrologueGameMode::APrologueGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/Player/Prologue/PrologueCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}



