// Fill out your copyright notice in the Description page of Project Settings.

#include "DC17mBlaster.h"


// Sets default values for this component's properties
UDC17mBlaster::UDC17mBlaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDC17mBlaster::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDC17mBlaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

