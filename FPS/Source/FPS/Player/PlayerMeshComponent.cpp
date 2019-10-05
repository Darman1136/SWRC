


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

void UPlayerMeshComponent::ActivatePlayerMesh() {
	ShowLoadAnimation();
}

void UPlayerMeshComponent::DeactivatePlayerMesh() {
	TriggerStopMainAction();
	ResetState();
	ShowHolsterAnimation();
}

void UPlayerMeshComponent::TriggerMainAction() {
	DoMainAction();
}

void UPlayerMeshComponent::DoMainAction() {}

void UPlayerMeshComponent::TriggerStopMainAction() {
	DoStopMainAction();
}

void UPlayerMeshComponent::DoStopMainAction() {}

void UPlayerMeshComponent::ShowLoadAnimation() {
	GetWorld()->GetTimerManager().SetTimer(ShowLoadMeshHandle, this, &UPlayerMeshComponent::ShowLoadAnimationMesh, .1f);
	bIsHolstering = false;
	bIsLoading = true;
}

void UPlayerMeshComponent::ShowLoadAnimationMesh() {
	SetVisibility(true, true);
}

void UPlayerMeshComponent::FinishLoadAnimation() {
	bIsActive = true;
	bIsLoading = false;
}

void UPlayerMeshComponent::ShowHolsterAnimation() {
	bIsActive = false;
	bIsHolstering = true;
	bIsLoading = false;
}

void UPlayerMeshComponent::FinishHolsterAnimation() {
	SetVisibility(false, true);
}

bool UPlayerMeshComponent::CanUseMainAction() {
	return !bIsLoading && !bIsHolstering;
}

void UPlayerMeshComponent::ResetState() {
	bIsActive = false;
	bIsLoading = false;
	bIsHolstering = false;
}


void UPlayerMeshComponent::TriggerZoom() {
	DoZoom();
}

void UPlayerMeshComponent::DoZoom() {}