// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "FPS.h"
#include "FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Engine/World.h"
#include "TimerManager.h"
#include "Player/PlayerMeshComponent.h"
#include "Camera/PlayerCameraManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AFPSCharacter

AFPSCharacter::AFPSCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->ComponentTags.Add(FName("FirstPersonCameraComponent"));

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

void AFPSCharacter::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();

	CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	DefaultFOV = CameraManager->GetFOVAngle();

	for (const TPair<EPlayerMeshType, UPlayerMeshComponent*>& PlayerMeshComponent : PlayerMeshComponentMap) {
		PlayerMeshComponent.Value->InitializeBeginPlay();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPSCharacter::OnFireReleased);

	// Bind reload event
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacter::OnReload);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AFPSCharacter::OnZoom);

	PlayerInputComponent->BindAction<FSwitchWeaponDelegate>("SwitchWeapon1", IE_Pressed, this, &AFPSCharacter::SwitchWeapon, EPlayerMeshType::DC15S);
	PlayerInputComponent->BindAction<FSwitchWeaponDelegate>("SwitchWeapon2", IE_Pressed, this, &AFPSCharacter::SwitchWeapon, EPlayerMeshType::DC17M);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AFPSCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSCharacter::LookUpAtRate);
}

void AFPSCharacter::OnResetVR() {
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AFPSCharacter::MoveForward(float Value) {
	if (Value != 0.0f) {
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSCharacter::MoveRight(float Value) {
	if (Value != 0.0f) {
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSCharacter::TurnAtRate(float Rate) {
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::LookUpAtRate(float Rate) {
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFPSCharacter::OnFirePressed() {
	if (!IsPlayerInputEnabled()) {
		return;
	}
	GetActivePlayerMeshComponent()->TriggerMainAction();
}

void AFPSCharacter::OnFireReleased() {
	if (!IsPlayerInputEnabled()) {
		return;
	}
	GetActivePlayerMeshComponent()->TriggerStopMainAction();
}

void AFPSCharacter::OnReload() {
	if (!IsPlayerInputEnabled()) {
		return;
	}
	OnReloadInternal();
}

void AFPSCharacter::OnReloadInternal() {
	ResetZoom();
}

void AFPSCharacter::OnZoom() {
	if (!IsPlayerInputEnabled()) {
		return;
	}
	bIsZooming = !bIsZooming && GetCastedPlayerMesh<UPlayerMeshComponent>()->CanZoom();
	OnZoomInternal();
}

void AFPSCharacter::OnZoomInternal() {
	if (bIsZooming) {
		EngageZoom();
	} else {
		ResetZoom();
	}
}

void AFPSCharacter::EngageZoom() {
	if (GetCastedPlayerMesh<UPlayerMeshComponent>()->CanZoom()) {
		bIsZooming = true;
		CameraManager->SetFOV(DefaultFOV * ZoomFactor);
	} else {
		ResetZoom();
	}
}

void AFPSCharacter::ResetZoom() {
	bIsZooming = false;
	CameraManager->SetFOV(DefaultFOV);
}

void AFPSCharacter::ActivatePlayerMesh(EPlayerMeshType Type) {
	if (PlayerMeshComponentMap.Contains(Type)) {
		NextActivePlayerMeshComponent = PlayerMeshComponentMap.FindRef(Type);
		if (ActivePlayerMeshComponent) {
			DeactivatePlayerMesh();
		} else if (NextActivePlayerMeshComponent) {
			ActivePlayerMeshComponent = NextActivePlayerMeshComponent;
			ActivePlayerMeshComponent->ActivatePlayerMesh();
		}
	} else if (Type == EPlayerMeshType::NONE) {
		NextActivePlayerMeshComponent = nullptr;
		if (ActivePlayerMeshComponent) {
			DeactivatePlayerMesh();
		}
	} else {
		UE_LOG(LogFPChar, Error, TEXT("Failed to switch mesh, missing EPlayerMeshType"))
	}
}

void AFPSCharacter::DeactivatePlayerMesh() {
	ResetZoom();
	if (ActivePlayerMeshComponent) {
		ActivePlayerMeshComponent->DeactivatePlayerMesh();
	}
}

void AFPSCharacter::FinishPlayerMeshLoadAnimation() {
	if (ActivePlayerMeshComponent) {
		ActivePlayerMeshComponent->FinishLoadAnimation();
	}
}

void AFPSCharacter::FinishPlayerMeshHolsterAnimation() {
	if (ActivePlayerMeshComponent) {
		ActivePlayerMeshComponent->FinishHolsterAnimation();
		if (NextActivePlayerMeshComponent) {
			ActivePlayerMeshComponent = NextActivePlayerMeshComponent;
			ActivePlayerMeshComponent->ActivatePlayerMesh();
		}
	}
}

void AFPSCharacter::AddPlayerMesh(EPlayerMeshType Type, UPlayerMeshComponent* PlayerMeshComponent, bool IsStartingMesh) {
	PlayerMeshComponentMap.Add(Type, PlayerMeshComponent);
	if (IsStartingMesh) {
		ActivatePlayerMesh(Type);
	}
}

void AFPSCharacter::SetPlayerInputEnabled(bool Enabled) {
	PlayerInputEnabled = Enabled;
}

void AFPSCharacter::SwitchWeapon(EPlayerMeshType Type) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GETENUMSTRING("EPlayerMeshType", Type));
	if (IsPlayerInputEnabled()) {
		ActivatePlayerMesh(Type);
	}
}
