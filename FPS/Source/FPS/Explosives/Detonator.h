

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Detonator.generated.h"

UCLASS()
class FPS_API ADetonator : public AActor {
	GENERATED_BODY()

public:
	ADetonator();

	virtual void TriggerDetonate();

protected:
	virtual void BeginPlay() override;

	virtual void Detonate();

protected:
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* DetonatorStaticMesh;

	UPROPERTY(EditDefaultsOnly, meta = (MetaClass = "Explosion"))
		UClass*  ExplosionActorClass;

	FTimerHandle DetonationTimerHandle;
};
