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

ADC17mBlasterProjectile::ADC17mBlasterProjectile(const FObjectInitializer& ObjectInitializer) {
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionComp);
	ProjectileMesh->SetMobility(EComponentMobility::Movable);
	ProjectileMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ProjectileMovement->ProjectileGravityScale = 0.f;

	CollisionComp->OnComponentHit.AddDynamic(this, &ADC17mBlasterProjectile::OnHit);
}

//void ADC17mBlasterProjectile::BeginPlay() {
//	UDC17mBlasterStats* WeaponStats = NewObject<UDC17mBlasterStats>(this);
//	if (WeaponStats && WeaponStats->GetMesh()) {
//		ProjectileMesh->SetStaticMesh(WeaponStats->GetMesh().Get());
//		ProjectileMesh->SetWorldScale3D(FVector(.05, .1, .05));
//		ProjectileMesh->AddLocalRotation(FQuat(FVector(0.f, 0.f, 1.f), 1.5708f));
//
//		//ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//
//	}
//}

void ADC17mBlasterProjectile::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	UDC17mBlasterStats* WeaponStats = NewObject<UDC17mBlasterStats>(this);
	if (WeaponStats && WeaponStats->GetMesh()) {
		ProjectileMesh->SetStaticMesh(WeaponStats->GetMesh().Get());
		ProjectileMesh->SetWorldScale3D(FVector(.05, .1, .05));
		ProjectileMesh->AddLocalRotation(FQuat(FVector(0.f, 0.f, 1.f), 1.5708f));

		//ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
}

void ADC17mBlasterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (OtherComp->IsSimulatingPhysics()) {
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		ABasicAICharacter* BasicAICharacter = Cast<ABasicAICharacter>(OtherActor);
		if (BasicAICharacter) {
			ABasicAIController* BasicAIController = BasicAICharacter->GetCastedController();
			BasicAIController->TakeDamage(GetProjectileOwner(), GetDamageType(), GetDamage(), Hit);
		}

		if (ImpactGenericParticleSystem) {
			FVector location = GetActorLocation() * 0.99f;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactGenericParticleSystem, location, GetActorRotation());
		}
		Destroy();
	}
}