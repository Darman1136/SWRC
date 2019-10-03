


#include "PlayerMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"

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
	TriggerStopMainAction();
	ResetState();
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
		UAnimInstance* AnimInstance = GetAnimInstance();
		if (AnimInstance != NULL) {
			AnimInstance->Montage_Play(LoadAnimation, 1.f);
			GetWorld()->GetTimerManager().SetTimer(ShowLoadMeshHandle, this, &UPlayerMeshComponent::ShowLoadAnimationMesh, .1f);
			return true;
		}
	}
	SetVisibility(true, true);
	return false;
}

void UPlayerMeshComponent::ShowLoadAnimationMesh() {
	SetVisibility(true, true);
}

void UPlayerMeshComponent::FinishLoadAnimation() {}

bool UPlayerMeshComponent::ShowHolsterAnimation() {
	if (HolsterAnimation != NULL) {
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

bool UPlayerMeshComponent::CanUseMainAction() {
	return true;
}

void UPlayerMeshComponent::ResetState() {}
