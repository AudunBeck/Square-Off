// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElementAbility1.h"

// Sets default values
AWaterElementAbility1::AWaterElementAbility1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaterElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * myBoltSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	/// Make the waterball go forward, where range is based on lifespan

	/// Add so that the first few frames, the waterbolt goes slow and afterwards go fast - Make bool so we can add (potentially) own animation to go along
}

void AWaterElementAbility1::setupAttack(ATori * newOwner, float lifeSpan, float boltSpeed)
{
	myOwner = newOwner;
	SetLifeSpan(lifeSpan);
	myBoltSpeed = boltSpeed;
}

void AWaterElementAbility1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != myOwner)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			// Make the target take damage
			Cast<ATori>(OtherActor)->recieveDamage(30.f * chargedHit);	// float value is temporary
			/// Add slow to target - Thinking making a "get slowed" function that takes in duration and severity of slow
		}
	}
}
