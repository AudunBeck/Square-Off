// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElement.h"
AWindElement::AWindElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWindElement::BeginPlay()
{
	Super::BeginPlay();
	maxBuffDur = ability2lifeSpan;
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	if (windUpTime > 0)
		windUpTime -= DeltaTime;

	if (windUpTime <= 0 && charging == true)
	{
		//Cast waterbolt
		AWindElementAbility1* temp;
		/// Under "myOwner->GetActorLocation() + myOwner->GetActorFowardVector()," add spawnpoint to socket in the hand
		temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + ability1Range * myOwner->GetActorForwardVector(), myOwner->GetActorRotation());
		temp->setupAttack(myOwner, ability1lifeSpan, boltSpeed, damage);

		UE_LOG(LogTemp, Warning, TEXT("WindElement Ability 1 fired"));
		myOwner->setRotationRate(myOwner->rotationRate);
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		charging = false;
	}

	// Ability 2
	if (buffDur > 0)
	{
		buffDur -= DeltaTime;
		if (buffDur <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("WindElementAbility 2 buffduration is 0."));
			counter = 1;
			myOwner->setMoveSpeed(myOwner->moveSpeed);
			tempTimer = 0.2f;	// Delay after ability2 register an attack and the time it takes to dash
		}
	}

	





	// Drit i dette
	if (tempTimer > 0)
	{
		tempTimer -= DeltaTime;
	}
}


void AWindElement::ability1()
{
	if (ammo1 > 0 && charging == false && myOwner->locked <= 0.f)
	{
		charging = true;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 1 charging up"));
		windUpTime = maxWindUpTime;
		myOwner->setRotationRate(0.f);
		myOwner->setMoveSpeed(myOwner->moveSpeed * 0.8);
	}
	Super::ability1();
}

void AWindElement::ability2()
{
	if (ammo2 > 0 && counter < 4)
	{
		buffDur = maxBuffDur;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has: %i, counters."), counter);

		AWindElementAbility2* temp;
		temp = GetWorld()->SpawnActor<AWindElementAbility2>(WindElementAbility2_BP, myOwner->GetActorLocation(), myOwner->GetActorRotation());
		
		if (counter == 1)
			//temp->setupAttack(myOwner, this, ability2lifeSpan, ability2Damage, radius1Count);
		if (counter == 2)
			//temp->setupAttack(myOwner, this, ability2lifeSpan, ability2Damage, radius2Count);
		if (counter == 3)
			//temp->setupAttack(myOwner, this, ability2lifeSpan, ability2Damage, radius3Count);

		counter++;
		Super::ability2();
	}
	else if (counter > 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has 3 stacks"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has no ammo"));
	}
}