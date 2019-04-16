// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"

AWindElementAbility2::AWindElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;

}

AWindElementAbility2::~AWindElementAbility2()
{
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	this->SetLifeSpan(myElement->buffDur);
	myPlayer->locked = true;
	myPlayer->setMoveSpeed(myPlayer->moveSpeed + myElement->bonusSpeed);
	// Stops collision towards other Tori's - Called in Blueprint
	stopCollision();
}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWindElementAbility2::startCollision()
{
	myPlayer->locked = false;
	myPlayer->setMoveSpeed(myPlayer->moveSpeed);
}

