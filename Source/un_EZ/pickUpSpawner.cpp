#include "pickUpSpawner.h"

ApickUpSpawner::ApickUpSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ApickUpSpawner::BeginPlay()
{
	Super::BeginPlay();
}

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

