

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explosion.generated.h"

UCLASS()
class FPS_API AExplosion : public AActor {
	GENERATED_BODY()

public:
	AExplosion();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class URadialForceComponent* RadialForceComponent;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* ExplosionParticleSystem;
};
