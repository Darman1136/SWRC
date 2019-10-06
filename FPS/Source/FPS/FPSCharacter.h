// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.h"
#include "Player/PlayerMeshComponent.h"
#include "Player/PlayerWeaponMeshComponent.h"
#include "Explosives/Thermal/ThermalDetonator.h"
#include "FPSCharacter.generated.h"

class UInputComponent;

DECLARE_DELEGATE_OneParam(FSwitchWeaponDelegate, EPlayerMeshType);

UCLASS(abstract, config = Game)
class AFPSCharacter : public ABasicCharacter {
	GENERATED_BODY()

public:
	AFPSCharacter();

	void OnFirePressed();

	void OnFireReleased();

	/** Reloads */
	void OnReload();

	void OnZoom();

	void OnMelee();

	void OnThrow();

	virtual void DoThrow();

	void EngageZoom();

	void ResetZoom();

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

	UFUNCTION(BlueprintCallable)
		void SetPlayerInputEnabled(bool Enabled);

	FORCEINLINE bool IsPlayerInputEnabled() const { return PlayerInputEnabled; }

	UFUNCTION(BlueprintPure, Category = "Player|Mesh")
		FORCEINLINE class UPlayerMeshComponent* GetActivePlayerMeshComponent() const { return ActivePlayerMeshComponent; }
	UFUNCTION(BlueprintPure, Category = "Player|Mesh")
		FORCEINLINE class UStaticMeshComponent* GetVisorMesh() const { return VisorMesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	virtual void FinishPlayerMeshLoadAnimation();

	virtual void FinishPlayerMeshHolsterAnimation();

	virtual void FinishPlayerMeshMeleeAnimation();

	virtual void FinishPlayerMeshThrowAnimation();

	virtual void CheckMeleeHit();

	UClass* GetSelectedDetonator() { return SelectedDetonator; }

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

	void DeactivatePlayerMesh();

	void AddPlayerMesh(EPlayerMeshType Type, UPlayerMeshComponent* PlayerMeshComponent, bool IsStartingMesh = false);

	void SwitchWeapon(EPlayerMeshType Type);

	template <typename UPlayerMeshComponent>
	UPlayerMeshComponent* GetCastedPlayerMesh() {
		return Cast<UPlayerMeshComponent>(GetActivePlayerMeshComponent());
	}

	virtual void OnReloadInternal();

	virtual void OnZoomInternal();

	virtual void OnMeleeInternal();

	virtual void OnThrowInternal();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* VisorMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, Category = "Mesh|Player")
		TMap<EPlayerMeshType, UPlayerMeshComponent*> PlayerMeshComponentMap;

	class APlayerCameraManager* CameraManager;

	UPROPERTY(EditAnywhere, Category = Weapon)
		float ZoomFactor = .6f;

	UPROPERTY(VisibleAnywhere)
		float DefaultFOV;

	bool bIsZooming = false;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = Mesh))
		class UPlayerMeshComponent* ActivePlayerMeshComponent;

	UClass* SelectedDetonator;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class UPlayerMeshComponent* NextActivePlayerMeshComponent;

	bool PlayerInputEnabled = true;

};

