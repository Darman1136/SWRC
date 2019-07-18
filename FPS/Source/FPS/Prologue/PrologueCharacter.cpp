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

APrologueCharacter::APrologueCharacter() : Super() {
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	//Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -0.f);

	VisorMeshBoy = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VisorMeshBoy"));
	VisorMeshBoy->SetOnlyOwnerSee(true);
	VisorMeshBoy->SetupAttachment(FirstPersonCameraComponent);
	VisorMeshBoy->bCastDynamicShadow = false;
	VisorMeshBoy->CastShadow = false;
	VisorMeshBoy->RelativeLocation = FVector(16.916187f, -0.115124f, -0.419205f);
	VisorMeshBoy->RelativeScale3D = FVector(0.3f, 0.8f, 0.55f);

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
	
	//// Create a gun mesh component
	//FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	//// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	//FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//FP_MuzzleLocation->SetupAttachment(FP_Gun);
	//FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	PrimaryActorTick.bCanEverTick = true;

	/* ignore collisions with trace channel "LookAtTraceChannel" defined by the editor in the DefaultEngine.ini */
	Mesh1P->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
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
	AController* Controller = GetController();
	if (Controller) {
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector ForwardVector = CameraManager->GetActorForwardVector();
		ForwardVector *= 600;

		FVector LookTraceVector = CameraLocation + ForwardVector;
		// DrawDebugLine(GetWorld(), CameraLocation, LookTraceVector, FColor::Red, false, 1.f);

		FHitResult LookTraceResult;
		GetWorld()->LineTraceSingleByChannel(LookTraceResult, CameraLocation, LookTraceVector, /* LookAtTraceChannel defined by the editor in the DefaultEngine.ini */ ECollisionChannel::ECC_GameTraceChannel2);
		if (LookTraceResult.bBlockingHit && LookTraceResult.GetActor()) {
			AActor* HitActor = LookTraceResult.GetActor();
			UE_LOG(LogTemp, Warning, TEXT("Trace %s"),
				*HitActor->GetName());
			if (HitActor->IsA(ABasicAICharacter::StaticClass())) {
				ABasicAICharacter* BasicAICharacter = Cast<ABasicAICharacter>(HitActor);
				ABasicAIController* BasicAIController = BasicAICharacter->GetCastedController<ABasicAIController>();
				BasicAIController->LookedAtByPlayer(this);
			}
		}
	}
}

void APrologueCharacter::OnFire() {
	Super::OnFire();
}


void APrologueCharacter::OnReload() {

}

void APrologueCharacter::SwitchToBoyMesh() {
	Mesh1P->SetVisibility(false);
	VisorMeshBoy->SetVisibility(true);
}

void APrologueCharacter::SwitchToVisorMesh() {
	VisorMeshBoy->SetVisibility(false);
	VisorMesh->SetVisibility(true);
}

void APrologueCharacter::SwitchToTrainingMesh() {
	Mesh1P->SetVisibility(false);
	VisorMeshBoy->SetVisibility(false);
}
