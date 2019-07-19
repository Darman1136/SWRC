


#include "PathNode.h"
#include "Components/BillboardComponent.h"


APathNode::APathNode() {
	BillboardComp = CreateDefaultSubobject< UBillboardComponent>(TEXT("BillboardComp"));
	BillboardComp->SetHiddenInGame(true, true);
	RootComponent = BillboardComp;
}

