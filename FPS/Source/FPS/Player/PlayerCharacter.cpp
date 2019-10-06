// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "FPSCharacter.h"
#include <Materials/MaterialInstanceDynamic.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include <EngineGlobals.h>
#include "Engine/World.h"
#include "TimerManager.h"
#include "FPSProjectile.h"
#include "Weapon/DC17mBlaster.h"
#include "Data/DC17mBlasterStats.h"
#include "Player/Mesh/PlayerDC17MMeshComponent.h"
#include "Player/Mesh/PlayerDC15SMeshComponent.h"

APlayerCharacter::APlayerCharacter() : Super() {
	PrimaryActorTick.bCanEverTick = true;

	PlayerDC17MMeshComponent = CreateDefaultSubobject<UPlayerDC17MMeshComponent>(TEXT("PlayerDC17MMesh"));
	PlayerDC17MMeshComponent->Initialize(this);
	AddPlayerMesh(PlayerDC17MMeshComponent->GetPlayerMeshType(), PlayerDC17MMeshComponent);

	PlayerDC15SMeshComponent = CreateDefaultSubobject<UPlayerDC15SMeshComponent>(TEXT("PlayerDC15SMesh"));
	PlayerDC15SMeshComponent->Initialize(this);
	AddPlayerMesh(PlayerDC15SMeshComponent->GetPlayerMeshType(), PlayerDC15SMeshComponent);

	VisorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisorMesh"));
	VisorMesh->SetOnlyOwnerSee(true);
	VisorMesh->SetupAttachment(FirstPersonCameraComponent);
	VisorMesh->bCastDynamicShadow = false;
	VisorMesh->CastShadow = false;
	VisorMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	VisorMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();
	ActivatePlayerMesh(EPlayerMeshType::DC17M);

	// Can't get DataTables to work properly without crashing sometimes
	/*
	WeaponStats = NewObject<UDC17mBlasterStats>(this);
	if (WeaponStats) {
		CurrentAmmo = WeaponStats->GetMaxAmmo();
		CurrentMagAmmo = WeaponStats->GetMagSize();
	}
	*/

	UMaterialInterface* VisorMaterial = VisorMesh->GetMaterial(0);
	if (VisorMaterial) {
		VisorMaterialInstance = UMaterialInstanceDynamic::Create(VisorMaterial, this);
		VisorMaterialInstance->SetVectorParameterValue("WiperTime", FVector(-3.f, 0.f, 0.f));
		UE_LOG(LogTemp, Warning, TEXT("Wipertime"));
		VisorMesh->SetMaterial(0, VisorMaterialInstance);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TestKey", IE_Pressed, this, &APlayerCharacter::StartWiper);
	PlayerInputComponent->BindAction("TestKey", IE_Released, this, &APlayerCharacter::ResetWiper);
}

void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (VisorWiperActive) {
		PlayWiper(DeltaTime);
	}
}

void APlayerCharacter::ReloadAmmoCount() {
	GetCastedPlayerMesh<UPlayerWeaponMeshComponent>()->ReloadAmmoCount();
}

void APlayerCharacter::OnReloadInternal() {
	Super::OnReloadInternal();
	GetCastedPlayerMesh<UPlayerWeaponMeshComponent>()->TriggerReload();
}

void APlayerCharacter::ReloadDone() {
	GetCastedPlayerMesh<UPlayerWeaponMeshComponent>()->ReloadDone();
}

void APlayerCharacter::OnZoomInternal() {
	Super::OnZoomInternal();
	GetCastedPlayerMesh<UPlayerWeaponMeshComponent>()->TriggerZoom();
}

void APlayerCharacter::OnMeleeInternal() {
	Super::OnMeleeInternal();
	GetCastedPlayerMesh<UPlayerWeaponMeshComponent>()->TriggerMeleeAction();
}

void APlayerCharacter::OnThrowInternal() {
	Super::OnThrowInternal();
	GetCastedPlayerMesh<UPlayerWeaponMeshComponent>()->TriggerThrowAction();
}

void APlayerCharacter::StartWiper() {
	VisorWiperActive = true;
	UE_LOG(LogTemp, Warning, TEXT("WIPE start"));
}

void APlayerCharacter::PlayWiper(float DeltaTime) {
	if (VisorMaterialInstance) {
		VisorWiperCurrentTime += DeltaTime;
		VisorMaterialInstance->SetVectorParameterValue("WiperTime", FVector(VisorWiperCurrentTime, 0.f, 0.f));
		int32 wipe = FMath::RandRange(0, 3);
		UE_LOG(LogTemp, Warning, TEXT("WIPE %d"), wipe);
		VisorMaterialInstance->SetScalarParameterValue("WiperInt", wipe);
	}
}

void APlayerCharacter::ResetWiper() {
	UE_LOG(LogTemp, Warning, TEXT("WIPE stop"));
	VisorWiperActive = false;
	if (VisorMaterialInstance) {
		VisorWiperCurrentTime = VisorWiperStartTime;
		VisorMaterialInstance->SetVectorParameterValue("WiperTime", FVector(VisorWiperCurrentTime, 0.f, 0.f));
	}
}
