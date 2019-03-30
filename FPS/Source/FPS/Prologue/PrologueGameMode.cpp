// Fill out your copyright notice in the Description page of Project Settings.

#include "PrologueGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
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

AActor* APrologueGameMode::ChoosePlayerStart_Implementation(AController* Player) {
	for (TActorIterator<APlayerStart> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		APlayerStart* PlayerStart = *ActorItr;
		if (PlayerStart->ActorHasTag(PlayerStartName)) {
			return PlayerStart;
		}
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}



