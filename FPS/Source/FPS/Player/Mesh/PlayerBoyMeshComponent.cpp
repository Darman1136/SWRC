


#include "PlayerBoyMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "FPSCharacter.h"

UPlayerBoyMeshComponent::UPlayerBoyMeshComponent() : Super() {
	PlayerMeshType = EPlayerMeshType::BOY;
	VisiorEnabled = false;
	bCanZoom = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ActualSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Meshes/HUD/Boy/HelmetBoy.HelmetBoy'"));
	if (ActualSkeletalMesh.Succeeded()) {
		SetSkeletalMesh(ActualSkeletalMesh.Object);
	}

	SetOnlyOwnerSee(true);
	bCastDynamicShadow = false;
	CastShadow = false;
	RelativeRotation = FRotator(0.f);
	RelativeLocation = FVector(2.f, 0.f, 0.f);
	RelativeScale3D = FVector(0.3f, 0.3f, 0.3f);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);

	BoyVisorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoyVisorMesh"));
	BoyVisorMesh->SetOnlyOwnerSee(true);
	BoyVisorMesh->SetupAttachment(this);
	BoyVisorMesh->bCastDynamicShadow = false;
	BoyVisorMesh->CastShadow = false;
	BoyVisorMesh->RelativeLocation = FVector(-1.f, 0.f, 0.f);
	BoyVisorMesh->RelativeScale3D = FVector(1.f, 1.5f, 1.f);
	BoyVisorMesh->SetVisibility(false, false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>StaticMeshBoyVisior(TEXT("StaticMesh'/Game/FirstPerson/StaticMeshes/HUD/Helmet/BoyHelmet.BoyHelmet'"));
	if (StaticMeshBoyVisior.Succeeded()) {
		BoyVisorMesh->SetStaticMesh(StaticMeshBoyVisior.Object);
	}
}

void UPlayerBoyMeshComponent::ShowHolsterAnimation() {
	bIsActive = false;
	FinishHolsterAnimation();
	Cast<AFPSCharacter>(Parent)->FinishPlayerMeshHolsterAnimation();
}

void UPlayerBoyMeshComponent::ShowLoadAnimation() {
	ShowLoadAnimationMesh();
	FinishLoadAnimation();
}