// Fill out your copyright notice in the Description page of Project Settings.

#include "DC17mBlasterProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Data/DC17mBlasterStats.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "AI/BasicAICharacter.h"
#include "AI/BasicAIController.h"
#include "Components/PointLightComponent.h"

ADC17mBlasterProjectile::ADC17mBlasterProjectile() : Super() {
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionComp);
	ProjectileMesh->SetMobility(EComponentMobility::Movable);
	ProjectileMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ProjectileMovement->ProjectileGravityScale = 0.f;

	ProjectilePointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("MyLight"));
	ProjectilePointLight->SetupAttachment(CollisionComp);
	ProjectilePointLight->SetIntensity(1000.f);
	ProjectilePointLight->SetAttenuationRadius(500);
	ProjectilePointLight->SetLightColor(FLinearColor(FColor(129, 134, 214)));

	CollisionComp->OnComponentHit.AddDynamic(this, &ADC17mBlasterProjectile::OnHit);
}

void ADC17mBlasterProjectile::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);
	UDC17mBlasterStats* WeaponStats = NewObject<UDC17mBlasterStats>(this);
	if (WeaponStats && WeaponStats->GetMesh()) {
		ProjectileMesh->SetStaticMesh(WeaponStats->GetMesh().Get());
	}
}

void ADC17mBlasterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((GetOwner() != OtherActor) && (OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		if (OtherComp->IsSimulatingPhysics()) {
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		ABasicAICharacter* BasicAICharacter = Cast<ABasicAICharacter>(OtherActor);
		if (BasicAICharacter) {
			ABasicAIController* BasicAIController = BasicAICharacter->GetCastedController<ABasicAIController>();
			BasicAIController->TakeDamageAI(GetOwner(), GetDamageType(), GetDamage(), Hit);
		}

		if (ImpactGenericParticleSystem) {
			FVector location = GetActorLocation();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactGenericParticleSystem, location, GetActorRotation());
		}
		Destroy();
	}
}