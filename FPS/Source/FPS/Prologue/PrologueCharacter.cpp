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
#include "AI/BasicAICharacter.h"
#include "AI/BasicAIController.h"

APrologueCharacter::APrologueCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	//Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -0.f);

	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->GravityScale = 0.f;
	CharacterMovementComponent->MaxWalkSpeed = 0.f;

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

