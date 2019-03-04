// Fill out your copyright notice in the Description page of Project Settings.

#include "pickUpSpawner.h"


// Sets default values
ApickUpSpawner::ApickUpSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ApickUpSpawner::BeginPlay()
{
	Super::BeginPlay();
	spawnElement();

}

// Called every frame
void ApickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ApickUpSpawner::spawnElement()
{
	if (ElementToSpawn != nullptr)
	{
		SpawnedElement = GetWorld()->SpawnActor<ApickUp>(ElementToSpawn, GetActorLocation(), FRotator::ZeroRotator);
		SpawnedElement->mySpawner = this;
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Missing PickUp!"));
}

