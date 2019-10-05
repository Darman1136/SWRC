


#include "PlayerHelmetMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Animation/AnimInstance.h"
#include "FPSCharacter.h"

UPlayerHelmetMeshComponent::UPlayerHelmetMeshComponent() : Super() {
	PlayerMeshType = EPlayerMeshType::PROLOGUE_HELMET;
	VisiorEnabled = false;
	bCanZoom = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>ActualSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Meshes/HUD/Helmet/HudArmsHelmet.HudArmsHelmet'"));
	if (ActualSkeletalMesh.Succeeded()) {
		SetSkeletalMesh(ActualSkeletalMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ActualAnimationBlueprint(TEXT("/Game/FirstPerson/Meshes/HUD/Helmet/HudArmsHelmet_Skeleton_AnimBlueprint"));
	if (ActualAnimationBlueprint.Succeeded()) {
		SetAnimInstanceClass(ActualAnimationBlueprint.Class);
	}

	SetOnlyOwnerSee(true);
	bCastDynamicShadow = false;
	CastShadow = false;
	RelativeLocation = FVector(7.f, 0.f, -1.f);
	RelativeScale3D = FVector(0.3f, 0.3f, 0.3f);
	SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
}

void UPlayerHelmetMeshComponent::DoAnimation() {
	if (AnimationMontage != NULL) {
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL && AnimInstance->GetCurrentActiveMontage() == NULL) {
			AnimInstance->Montage_Play(AnimationMontage, 1.f);
		}
	}
}

void UPlayerHelmetMeshComponent::ShowHolsterAnimation() {
	bIsActive = false;
	FinishHolsterAnimation();
	Cast<AFPSCharacter>(Parent)->FinishPlayerMeshHolsterAnimation();
}

void UPlayerHelmetMeshComponent::ShowLoadAnimation() {
	ShowLoadAnimationMesh();
	FinishLoadAnimation();
}