// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Weapon/Projectile/WeaponDamageType.h"
#include "Weapon/Projectile/DamageAreaEnum.h"
#include "BasicAICharacter.h"
#include "FPS.h"
#include "Components/CapsuleComponent.h"
#include "Common/DismembermentActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

const FName ABasicAIController::BKIsAlive = FName("IsAlive");
const FName ABasicAIController::BKTarget = FName("Target");
const FName ABasicAIController::BKTargetLocation = FName("TargetLocation");

ABasicAIController::ABasicAIController() : Super() {
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
}

void ABasicAIController::OnPossess(class APawn* InPawn) {
	Super::OnPossess(InPawn);
	SetPawn(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("Possess"));
}

void ABasicAIController::BeginPlay() {
	Super::BeginPlay();

	if (GetCastedPawn<ABasicAICharacter>()->IsAutoStartBehaviorTree()) {
		StartBehaviorTree();
	}
}


void ABasicAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

int32 ABasicAIController::GetHealth() {
	return Health;
}

void ABasicAIController::TakeDamageAI(AActor* AttackingActor, EWeaponDamageType DamageType, float amount, const FHitResult& Hit) {
	Health -= amount * GetTakenDamageMultiplier(Hit.BoneName);
	if (Health < 0) {
		Health = 0;
		OnDeath(Hit.BoneName);
	}
	// UE_LOG(LogTemp, Warning, TEXT("Health: %d, Type: %s, Amount: %f, Attacker: %s, Bone: %s, DamageAreaByBone: %s"), Health, *GETENUMSTRING("EWeaponDamageType", DamageType), amount, *AttackingActor->GetName(), *Hit.BoneName.ToString(), *GETENUMSTRING("EDamageArea", DamageArea));
}

void ABasicAIController::TurnHeadToObject(AActor* Actor) {
}

float ABasicAIController::GetTakenDamageMultiplier(FName Bone) {
	if (!Bone.IsNone()) {
		if (HitBoneToDamageMultiplierMap.Contains(Bone)) {
			return HitBoneToDamageMultiplierMap.FindRef(Bone);
		}
	}
	return 1.f;
}

void ABasicAIController::OnDeath(FName Bone) {
	BlackboardComp->SetValueAsBool(ABasicAIController::BKIsAlive, false);

	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn->IsA(ABasicAICharacter::StaticClass())) {
		ABasicAICharacter* CurrentCharacter = Cast<ABasicAICharacter>(CurrentPawn);
		CurrentCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (!Bone.IsNone()) {
		if (HitBoneToSpawnBoneMap.Contains(Bone)) {
			FName SpawnBone = HitBoneToSpawnBoneMap.FindRef(Bone);
			if (!SpawnBone.IsNone() && SpawnBoneToStaticMeshMap.Contains(SpawnBone) && SpawnBoneToSpawnChanceMap.Contains(SpawnBone)) {
				float SpawnChance = SpawnBoneToSpawnChanceMap.FindRef(SpawnBone);
				if (SpawnChance >= FMath::RandRange(0.f, 1.f)) {
					Dismember(SpawnBone, SpawnBoneToStaticMeshMap.FindRef(SpawnBone));
				}
			}
		}
	}
	if (FAIDeath_OnDeath.IsBound()) {
		FAIDeath_OnDeath.Broadcast();
	}
}

void ABasicAIController::Dismember(FName Bone, UStaticMesh* MeshToSpawn) {
	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn->IsA(ABasicAICharacter::StaticClass())) {
		ABasicAICharacter* CurrentCharacter = Cast<ABasicAICharacter>(CurrentPawn);
		if (CurrentCharacter) {
			USkeletalMeshComponent* SMesh = CurrentCharacter->GetMesh();
			SMesh->HideBoneByName(Bone, EPhysBodyOp::PBO_Term);


			FTransform SocketTransform = SMesh->GetSocketTransform(FName(*(Bone.ToString() + "Socket")));
			
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ActorSpawnParams.Owner = CurrentCharacter;
			ADismembermentActor* SpawnedActor = GetWorld()->SpawnActor<ADismembermentActor>( ADismembermentActor::StaticClass(), SocketTransform.GetLocation(), FRotator(SocketTransform.GetRotation()), ActorSpawnParams);
			if (SpawnedActor) {
				SpawnedActor->GetStaticMesh()->SetStaticMesh(MeshToSpawn);
			}
		}
	}
}

void ABasicAIController::LookedAtByPlayer(AActor* PlayerActor) {
}

void ABasicAIController::StartBehaviorTree() {
	UE_LOG(LogTemp, Warning, TEXT("StartBehaviorTree"));
	if (BehaviorTree) {
		BlackboardComp->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
		if (BlackboardComp != nullptr) {
			InitializeBlackboardWithValues();
		}
		UE_LOG(LogTemp, Warning, TEXT("Running BehaviorTree"));
		RunBehaviorTree(BehaviorTree);
	}
}

void ABasicAIController::InitializeBlackboardWithValues() {
	APawn* CurrentPawn = GetPawn();
	if (CurrentPawn && CurrentPawn->IsA(ABasicAICharacter::StaticClass())) {
		ABasicAICharacter* BasicCharacter = Cast<ABasicAICharacter>(CurrentPawn);
		TMap<FName, AActor*> ObjectMap = BasicCharacter->GetBlackboardObjectMap();
		if (ObjectMap.Num() > 0) {
			for (auto& Entry : ObjectMap) {
				UE_LOG(LogTemp, Warning, TEXT("ObjectMap: %s # %s"), *Entry.Key.ToString(), *Entry.Value->GetName());
				BlackboardComp->SetValueAsObject(Entry.Key, Entry.Value);
			}
		}
	}
	BlackboardComp->SetValueAsBool(ABasicAIController::BKIsAlive, true);
}
