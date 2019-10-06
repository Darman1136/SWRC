


#include "Explosion.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AExplosion::AExplosion() {
	PrimaryActorTick.bCanEverTick = false;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 800;
	RadialForceComponent->ImpulseStrength = 300000.f;
	RadialForceComponent->ForceStrength = 1000.f;
	RadialForceComponent->Falloff = ERadialImpulseFalloff::RIF_Linear;
}

void AExplosion::BeginPlay() {
	Super::BeginPlay();

	SetLifeSpan(5.f);
	RadialForceComponent->FireImpulse();
	if (ExplosionParticleSystem) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, GetActorLocation());
	}
}
