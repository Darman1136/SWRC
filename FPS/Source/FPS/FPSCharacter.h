// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.h"
#include "Player/PlayerMeshComponent.h"
#include "FPSCharacter.generated.h"

class UInputComponent;


UCLASS(abstract, config = Game)
class AFPSCharacter : public ABasicCharacter {
	GENERATED_BODY()

public:
	AFPSCharacter();

	void OnFirePressed();

	void OnFireReleased();

	/** Reloads */
	virtual void OnReload();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	FORCEINLINE class UPlayerMeshComponent* GetActivePlayerMeshComponent() const { return ActivePlayerMeshComponent; }

	FORCEINLINE class UStaticMeshComponent* GetVisorMesh() const { return VisorMesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		uint32 bUsingMotionControllers : 1;

protected:
	virtual void BeginPlay();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Mesh|Player")
	void ActivatePlayerMesh(EPlayerMeshType Type);

	void AddPlayerMesh(EPlayerMeshType Type, UPlayerMeshComponent* PlayerMeshComponent, bool IsStartingMesh = false);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* VisorMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh|Player")
		TMap<EPlayerMeshType, UPlayerMeshComponent*> PlayerMeshComponentMap;

private:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UPlayerMeshComponent* ActivePlayerMeshComponent;

};

