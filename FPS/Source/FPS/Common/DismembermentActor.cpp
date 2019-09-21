


#include "DismembermentActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADismembermentActor::ADismembermentActor() : Super() {
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DismembermentMesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetSimulatePhysics(true);
}

void ADismembermentActor::BeginPlay() {
	Super::BeginPlay();

}


