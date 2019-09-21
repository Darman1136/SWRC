

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DismembermentActor.generated.h"

UCLASS()
class FPS_API ADismembermentActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADismembermentActor();

	FORCEINLINE class UStaticMeshComponent* GetStaticMesh() const { return MeshComponent; }

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category = Dismemberment)
		class UStaticMeshComponent* MeshComponent;

};
