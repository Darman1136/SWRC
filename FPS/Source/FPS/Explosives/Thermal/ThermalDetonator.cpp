


#include "ThermalDetonator.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AThermalDetonator::AThermalDetonator() : Super() {
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ActualStaticMesh(TEXT("StaticMesh'/Game/FirstPerson/StaticMeshes/Weapons/Clone/ThermalDetonator.ThermalDetonator'"));
	if (ActualStaticMesh.Succeeded()) {
		DetonatorStaticMesh->SetStaticMesh(ActualStaticMesh.Object);
		DetonatorStaticMesh->RelativeScale3D = FVector(.3f);
	}
}