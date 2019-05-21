// Fill out your copyright notice in the Description page of Project Settings.

#include "UIHandler.h"
#include "Engine/Classes/GameFramework/PlayerController.h"

// Sets default values
AUIHandler::AUIHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUIHandler::BeginPlay()
{
	Super::BeginPlay();
	playersHitPointPercent.Init(0, 4);
	if (Camera != nullptr)
	{
		playerAmount = Camera->playerAmount;
		setLength();
	}
}

// Called every frame
void AUIHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	getPlayers();
}

void AUIHandler::getPlayers()
{
	for (int i = 0; i < playerAmount; i++)
	{
		ATori* tempRef = Cast<ATori>(Camera->playerControllers[i]->GetPawn());
		
		if (tempRef)
		{
			playersHitPointPercent[i] = tempRef->hitPointPercentage;
		}
		else
		{
			playersHitPointPercent[i] = 0.f;
		}
	}
}

void AUIHandler::setLength()
{
	float temp = fullLength / playerAmount;
	lengthBetween = temp - (temp / playerAmount);
	setBarPositions();
}
