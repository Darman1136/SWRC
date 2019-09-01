


#include "PlayerBoyMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

UPlayerBoyMeshComponent::UPlayerBoyMeshComponent() : Super() {
	PlayerMeshType = EPlayerMeshType::BOY;
	VisiorEnabled = false;

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

}