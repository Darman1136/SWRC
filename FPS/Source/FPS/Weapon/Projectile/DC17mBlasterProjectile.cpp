// Fill out your copyright notice in the Description page of Project Settings.

#include "DC17mBlasterProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Data/DC17mBlasterStats.h"


ADC17mBlasterProjectile::ADC17mBlasterProjectile() {
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(CollisionComp);
	ProjectileMesh->SetMobility(EComponentMobility::Movable);
	ProjectileMesh->SetCollisionProfileName(TEXT("NoCollision"));

	ProjectileMovement->ProjectileGravityScale = 0.f;
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
