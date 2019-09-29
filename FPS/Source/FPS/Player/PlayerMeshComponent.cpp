


#include "PlayerMeshComponent.h"
#include "Animation/AnimInstance.h"

UPlayerMeshComponent::UPlayerMeshComponent() {
	PlayerMeshType = EPlayerMeshType::NONE;
}

void UPlayerMeshComponent::BeginPlay() {
	Super::BeginPlay();
}

void UPlayerMeshComponent::Initialize(AActor* CurrentParent) {
	SetVisibility(false, true);
	Parent = CurrentParent;
	TArray<UCameraComponent*> CameraComponents;
	Parent->GetComponents<UCameraComponent>(CameraComponents);
	if (CameraComponents.Num() == 1) {
		Camera = CameraComponents[0];
		SetupAttachment(Camera);
	} else {
		UE_LOG(LogPlayerMeshComponent, Warning, TEXT("Failed to set parent for UPlayerMeshComponent"));
	}
}

void UPlayerMeshComponent::InitializeBeginPlay() {}

bool UPlayerMeshComponent::ActivatePlayerMesh() {
	return ShowLoadAnimation();
}

bool UPlayerMeshComponent::DeactivatePlayerMesh() {
	return ShowHolsterAnimation();
}

void UPlayerMeshComponent::TriggerMainAction() {
	DoMainAction();
}

void UPlayerMeshComponent::DoMainAction() {}

void UPlayerMeshComponent::TriggerStopMainAction() {
	DoStopMainAction();
}

void UPlayerMeshComponent::DoStopMainAction() {}

bool UPlayerMeshComponent::ShowLoadAnimation() {
	if (LoadAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL) {
			AnimInstance->Montage_Play(LoadAnimation, 1.f);
			SetVisibility(true, true);
			return true;
		}
	}
	SetVisibility(true, true);
	return false;
}

void UPlayerMeshComponent::FinishLoadAnimation() {}

bool UPlayerMeshComponent::ShowHolsterAnimation() {
	if (HolsterAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL) {
			AnimInstance->Montage_Play(HolsterAnimation, 1.f);
			return true;
		}
	}
	return false;
}

void UPlayerMeshComponent::FinishHolsterAnimation() {
	SetVisibility(false, true);
}
