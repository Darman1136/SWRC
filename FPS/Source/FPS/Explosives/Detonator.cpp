


#include "Detonator.h"
#include "Components/StaticMeshComponent.h"
#include "Explosives/Explosion.h"
#include "Engine/World.h"
#include "TimerManager.h"

ADetonator::ADetonator() {
	PrimaryActorTick.bCanEverTick = true;

	DetonatorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DetonatorStaticMesh"));
	DetonatorStaticMesh->SetupAttachment(RootComponent);
	DetonatorStaticMesh->SetSimulatePhysics(true);
}

void ADetonator::BeginPlay() {
	Super::BeginPlay();

}

void ADetonator::TriggerDetonate() {
	GetWorld()->GetTimerManager().SetTimer(DetonationTimerHandle, this, &ADetonator::Detonate, 5.f);
}

void ADetonator::Detonate() {
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParams.Owner = GetOwner();
	AExplosion* SpawnedExplosion = GetWorld()->SpawnActor<AExplosion>(ExplosionActorClass, GetActorLocation(), FRotator(), ActorSpawnParams);
	Destroy();
}