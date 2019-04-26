// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElement.h"
#include "GameFramework/CharacterMovementComponent.h"
AWindElement::AWindElement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWindElement::BeginPlay()
{
	Super::BeginPlay();
	channelTime = 0;
	maxChannelTime = maxInterval * 3;
	ability1Damage = aility1DamageScalar;
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	//if (channelingAbility1 == true && channelTime <= maxChannelTime)
	//{
	//	channelTime += DeltaTime;
	//	if (interval <= 0)
	//	{
	//		interval = maxInterval;
	//		myOwner->setMoveSpeed(myOwner->moveSpeed * 0.3);

	//		AWindElementAbility1* temp;
	//		FActorSpawnParameters tempParam;
	//		tempParam.Owner = this;
	//		temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
	//			myOwner->GetActorRotation(), tempParam);
	//		ability1Damage += aility1DamageScalar;
	//		
	//	}
	//}
	//if ((channelingAbility1 == false && channelTime > 0) || channelTime >= maxChannelTime)
	//{
	//	myOwner->setMoveSpeed(myOwner->moveSpeed);
	//	channelTime = 0;
	//	ability1Damage = aility1DamageScalar;
	//}

	//if (interval > 0)
	//	interval -= DeltaTime;

	// Ability 2
}


void AWindElement::ability1()
{
	Super::ability1();
}

void AWindElement::ability1FireCode()
{
	AWindElementAbility1* temp;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
		myOwner->GetActorRotation(), tempParam);
	combo += 1;
}

void AWindElement::ability2()
{
	if (!windUsingAbility2)
	{
		AWindElementAbility2* temp;
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<AWindElementAbility2>(WindElementAbility2_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);
	}
}

void AWindElement::ability2FireCode()
{
}



int AWindElement::returnElementType()
{
	Super::returnElementType();
	return 4;
}
