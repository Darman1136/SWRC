


#include "PlayerBabyMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimInstance.h"
#include "FPSCharacter.h"

UPlayerBabyMeshComponent::UPlayerBabyMeshComponent() : Super() {
	PlayerMeshType = EPlayerMeshType::BABY;
	VisiorEnabled = false;
	bCanZoom = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ActualSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Meshes/HUD/Baby/baby.baby'"));
	if (ActualSkeletalMesh.Succeeded()) {
		SetSkeletalMesh(ActualSkeletalMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ActualAnimationBlueprint(TEXT("/Game/FirstPerson/Meshes/HUD/Baby/ABBaby"));
	if (ActualAnimationBlueprint.Succeeded()) {
		SetAnimInstanceClass(ActualAnimationBlueprint.Class);
	}

	SetOnlyOwnerSee(true);
	bCastDynamicShadow = false;
	CastShadow = false;
	RelativeRotation = FRotator(0.f);
	RelativeLocation = FVector(10.f, 0.f, 8.f);
	RelativeScale3D = FVector(0.3f, 0.3f, 0.3f);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
}

void UPlayerBabyMeshComponent::DoMainAction() {
	if (MainActionAnimation != NULL) {
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL && AnimInstance->GetCurrentActiveMontage() == NULL) {
			AnimInstance->Montage_Play(MainActionAnimation, 1.f);
		}
	}
}

void UPlayerBabyMeshComponent::ShowHolsterAnimation() {
	bIsActive = false;
	FinishHolsterAnimation();
	Cast<AFPSCharacter>(Parent)->FinishPlayerMeshHolsterAnimation();
}