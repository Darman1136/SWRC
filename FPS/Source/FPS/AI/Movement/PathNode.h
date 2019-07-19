

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathNode.generated.h"

UCLASS()
class FPS_API APathNode : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APathNode();

private:
	UPROPERTY(EditDefaultsOnly)
		class UBillboardComponent* BillboardComp;

};
