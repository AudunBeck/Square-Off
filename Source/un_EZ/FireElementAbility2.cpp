// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElementAbility2.h"

// Sets default values
AFireElementAbility2::AFireElementAbility2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFireElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sets the hitbox ahead of the player while flying forward
	this->SetActorLocation(myOwner->GetActorForwardVector() * attackRange + myOwner->GetActorLocation());
	this->SetActorRotation(myOwner->GetActorRotation());
}

void AFireElementAbility2::setupAttack(ATori * newOwner, float lifeSpan, float range)
{
	myOwner = newOwner;
	SetLifeSpan(lifeSpan);
	attackRange = range;
}
