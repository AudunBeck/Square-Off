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
	if (buffDur > 0)
	{
		myOwner->locked = 1.f;
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		buffDur -= DeltaTime;
	}
	if (buffDur <= 0)
	{
		myOwner->locked = 0.f;
		myOwner->setMoveSpeed(myOwner->moveSpeed);
	}
}

void AWaterElement::ability1()
{
	if (ammo1 > 0 && charging == false)
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
		buffDur = maxBuffDur;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 is fired"));
		AWaterElementAbility2* temp;
		temp = GetWorld()->SpawnActor<AWaterElementAbility2>(WaterElementAbility2_BP, myOwner->GetActorLocation(), myOwner->GetActorRotation());
		temp->setupAttack(this, ability2lifeSpan, dashDist, ability2CcDur, ability2Slow, ability2Damage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has no ammo"));
	}
}
