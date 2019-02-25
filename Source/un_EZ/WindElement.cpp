// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElement.h"
AWindElement::AWindElement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWindElement::BeginPlay()
{
	Super::BeginPlay();
	channelTime = maxChannelTime;
	ability2Damage = MaxAbility2Damage;
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	if (windUpTime > 0)
		windUpTime -= DeltaTime;

	// Ability 2
	if (myOwner->channelingAbility2 == true)
	{
		channelTime -= DeltaTime;
		if (channelTime > 0 && interval <= 0)
		{
			interval = maxInterval;
			myOwner->setMoveSpeed(myOwner->moveSpeed * 0.3);
			ability2();
		}
	}
	if (myOwner->channelingAbility2 == false && channelTime < maxChannelTime)
	{
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		channelTime += DeltaTime;
	}
	if (channelTime != 0)
	{
		ability2Damage = (MaxAbility2Damage / maxChannelTime) * channelTime;
		distance = (maxDistance / maxChannelTime )* channelTime;
	}
	if (interval > 0)
		interval -= DeltaTime;

}


void AWindElement::ability1()
{
	if (ammo1 > 0 && myOwner->locked <= 0.f)
	{
		AWindElementAbility1* temp;
		/// Under "myOwner->GetActorLocation() + myOwner->GetActorFowardVector()," add spawnpoint to socket in the hand
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);
	}
	//Super::ability1();
}

void AWindElement::ability2()
{
	if (channelTime > 0)
	{
		myOwner->locked = myOwner->globalCooldown;
		
		AWindElementAbility2* temp;
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<AWindElementAbility2>(WindElementAbility2_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);
		//Super::ability2();
	}
}

int AWindElement::returnElementType()
{
	Super::returnElementType();
	return 4;
}
