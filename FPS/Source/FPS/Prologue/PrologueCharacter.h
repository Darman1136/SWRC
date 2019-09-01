// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/AudioComponent.h"
#include "PrologueCharacter.generated.h"

/**
 *
 */
UCLASS(config = Game)
class FPS_API APrologueCharacter : public AFPSCharacter {
	GENERATED_BODY()


public:
	APrologueCharacter();

	UFUNCTION(BlueprintPure, Category = "Speech|Audio")
		UAudioComponent* GetSpeechAudioComponent() { return SpeechAudioComponent; }

	UFUNCTION(BlueprintPure, Category = "Ambient|Audio")
		UAudioComponent* GetAmbientAudioComponent() { return AmbientAudioComponent; }

	UFUNCTION(BlueprintPure, Category = "Music|Audio")
		UAudioComponent* GetMusicAudioComponent() { return MusicAudioComponent; }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	void SendLookRay();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Speech|Audio")
		class UAudioComponent* SpeechAudioComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Ambient|Audio")
		class UAudioComponent* AmbientAudioComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Music|Audio")
		class UAudioComponent* MusicAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh|Player|Baby")
		class UPlayerBabyMeshComponent* PlayerBabyMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh|Player|Boy")
		class UPlayerBoyMeshComponent* PlayerBoyMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh|Player|Helmet")
		class UPlayerHelmetMeshComponent* PlayerHelmetMeshComponent;

private:
	APlayerCameraManager* CameraManager;

};
