// Fill out your copyright notice in the Description page of Project Settings.

#include "PrologueCharacter.h"
#include "FPSCharacter.h"
//#include "Animation/AnimInstance.h"
//#include "Camera/CameraComponent.h"
//#include <Runtime/Engine/Classes/Engine/Engine.h>
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
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "AI/BasicAICharacter.h"
#include "AI/BasicAIController.h"
#include "Player/Mesh/PlayerBabyMeshComponent.h"
#include "Player/Mesh/PlayerBoyMeshComponent.h"

APrologueCharacter::APrologueCharacter() : Super() {
	PlayerBabyMeshComponent = CreateDefaultSubobject<UPlayerBabyMeshComponent>(TEXT("PlayerBabyMesh"));
	PlayerBabyMeshComponent->Initialize(this);
	AddPlayerMesh(PlayerBabyMeshComponent->GetPlayerMeshType(), PlayerBabyMeshComponent, true);

	PlayerBoyMeshComponent = CreateDefaultSubobject<UPlayerBoyMeshComponent>(TEXT("PlayerBoyMesh"));
	PlayerBoyMeshComponent->Initialize(this);
	AddPlayerMesh(PlayerBoyMeshComponent->GetPlayerMeshType(), PlayerBoyMeshComponent, false);

	VisorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisorMesh"));
	VisorMesh->SetOnlyOwnerSee(true);
	VisorMesh->SetupAttachment(FirstPersonCameraComponent);
	VisorMesh->bCastDynamicShadow = false;
	VisorMesh->CastShadow = false;
	VisorMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	VisorMesh->RelativeLocation = FVector(16.916187f, -0.115124f, -0.419205f);
	VisorMesh->RelativeScale3D = FVector(0.3f, 0.8f, 0.55f);

	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->GravityScale = 0.f;
	CharacterMovementComponent->MaxWalkSpeed = 0.f;

	SpeechAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SpeechAudioComponent"));

	AmbientAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientAudioComponent"));

	MusicAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicAudioComponent"));


	PrimaryActorTick.bCanEverTick = true;

	/* ignore collisions with trace channel "LookAtTraceChannel" defined by the editor in the DefaultEngine.ini */
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
}

void APrologueCharacter::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	SpeechAudioComponent->SetAutoActivate(false);
	AmbientAudioComponent->SetAutoActivate(false);
}

void APrologueCharacter::BeginPlay() {
	Super::BeginPlay();
	CameraManager = Cast<APlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

	/*
	if (CameraManager)
	{
		CameraManager->ViewYawMin = -200.f;
		CameraManager->ViewYawMax = 280.f;

		CameraManager->ViewPitchMin = -20.f;
		CameraManager->ViewPitchMax = 30.f;

	}
	*/
}

void APrologueCharacter::Tick(float DeltaTime) {
	SendLookRay();
}

void APrologueCharacter::SendLookRay() {
	AController* CurrentController = GetController();
	if (CurrentController) {
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector ForwardVector = CameraManager->GetActorForwardVector();
		ForwardVector *= 600;

		FVector LookTraceVector = CameraLocation + ForwardVector;
		// DrawDebugLine(GetWorld(), CameraLocation, LookTraceVector, FColor::Red, false, 1.f);

		FHitResult LookTraceResult;
		GetWorld()->LineTraceSingleByChannel(LookTraceResult, CameraLocation, LookTraceVector, /* LookAtTraceChannel defined by the editor in the DefaultEngine.ini */ ECollisionChannel::ECC_GameTraceChannel2);
		if (LookTraceResult.bBlockingHit && LookTraceResult.GetActor()) {
			AActor* HitActor = LookTraceResult.GetActor();
			// UE_LOG(LogTemp, Warning, TEXT("Trace %s"), *HitActor->GetName());
			if (HitActor->IsA(ABasicAICharacter::StaticClass())) {
				ABasicAICharacter* BasicAICharacter = Cast<ABasicAICharacter>(HitActor);
				ABasicAIController* BasicAIController = BasicAICharacter->GetCastedController<ABasicAIController>();
				BasicAIController->LookedAtByPlayer(this);
			}
		}
	}
}

void APrologueCharacter::OnReload() {}
