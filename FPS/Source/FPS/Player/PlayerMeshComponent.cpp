


#include "PlayerMeshComponent.h"

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

void UPlayerMeshComponent::Activate() {
	SetVisibility(true);
	ShowLoadAnimation();
}

void UPlayerMeshComponent::Deactivate() {
	SetVisibility(false);
}

void UPlayerMeshComponent::TriggerMainAction() {}

void UPlayerMeshComponent::DoMainAction() {}

void UPlayerMeshComponent::TriggerStopMainAction() {}

void UPlayerMeshComponent::DoStopMainAction() {}

void UPlayerMeshComponent::ShowLoadAnimation() {}

void UPlayerMeshComponent::ShowHolsterAnimation() {}

