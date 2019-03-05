// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElement.h"
AWindElement::AWindElement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWindElement::BeginPlay()
{
	Super::BeginPlay();
	channelTime = 0;
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	if (channelingAbility1 == true && channelTime <= maxChannelTime)
	{
		channelTime += DeltaTime;
		if (interval <= 0)
		{
			interval = maxInterval;
			myOwner->setMoveSpeed(myOwner->moveSpeed * 0.3);

			AWindElementAbility1* temp;
			FActorSpawnParameters tempParam;
			tempParam.Owner = this;
			temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
				myOwner->GetActorRotation(), tempParam);
		}
	}
	if (channelingAbility1 == false && channelTime > 0)
	{
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		channelTime -= DeltaTime;
	}
	if (channelTime >= maxChannelTime)
	{
		channelTime = 0;
		/// Cast pushback ability
	}
	if (channelTime != 0)
	{
		ability2Damage = (MaxAbility1Damage / maxChannelTime) * channelTime;
		distance = (maxDistance / maxChannelTime) * channelTime;
	}
	if (interval > 0)
		interval -= DeltaTime;

	// Ability 2
}


void AWindElement::ability1()
{
	//Super::ability1();
}

void AWindElement::ability2()
{
}

void AWindElement::ability2End()
{
	myOwner->setMoveSpeed(myOwner->moveSpeed);
	myOwner->currentSpeed = myOwner->moveSpeed;
	channelTime = 0;
}

int AWindElement::returnElementType()
{
	Super::returnElementType();
	return 4;
}
