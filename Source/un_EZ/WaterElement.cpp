// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElement.h"

// Sets default values
AWaterElement::AWaterElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaterElement::BeginPlay()
{
	Super::BeginPlay();
	maxBuffDur = ability2lifeSpan;
}

// Called every frame
void AWaterElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	if (windUpTime > 0)
		windUpTime -= DeltaTime;

	if(windUpTime <= 0 && charging == true)
	{
		//Cast waterbolt
		AWaterElementAbility1* temp;
		/// Under "myOwner->GetActorLocation() + myOwner->GetActorFowardVector()," add spawnpoint to socket in the hand
		temp = GetWorld()->SpawnActor<AWaterElementAbility1>(WaterElementAbility1_BP, myOwner->GetActorLocation() + ability1Range * myOwner->GetActorForwardVector(), myOwner->GetActorRotation());
		
		if (counter > 0)
			temp->setupAttack(myOwner, ability1lifeSpan, boltSpeedBuffed, ccDurBuffed, slowBuffed, damageBuffed);
		else
			temp->setupAttack(myOwner, ability1lifeSpan, boltSpeed, ccDur, slow, damage);
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 1 fired"));
		myOwner->setRotationRate(myOwner->rotationRate);
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		charging = false;
	}

	// Ability 2
	if (buffDur >= 0)
	{
		buffDur -= DeltaTime;
		if (buffDur <= 0)
		{
			myOwner->setMoveSpeed(myOwner->moveSpeed);
			myOwner->damageMultiplier = 1;
			tempTimer = 0.2f;	// Delay after ability2 register an attack and the time it takes to dash
		}
	}
	if (tempTimer > 0)
	{
		tempTimer -= DeltaTime;
		if(tempTimer <= 0.f)
			myOwner->SetActorEnableCollision(true);
	}
}

void AWaterElement::ability1()
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

void AWaterElement::ability2()
{
	if (ammo2 > 0)
	{
		myOwner->SetActorEnableCollision(false);
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		myOwner->currentSpeed = 0.f;
		myOwner->damageMultiplier = 0;
		buffDur = maxBuffDur;
		myOwner->locked = buffDur;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 ammo: %i"), ammo2);
		AWaterElementAbility2* temp;
		temp = GetWorld()->SpawnActor<AWaterElementAbility2>(WaterElementAbility2_BP, myOwner->GetActorLocation(), myOwner->GetActorRotation());
		temp->setupAttack(myOwner, this, ability2lifeSpan, dashDist, ability2CcDur, ability2Slow, ability2Damage);
		Super::ability2();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has no ammo"));
	}
}
