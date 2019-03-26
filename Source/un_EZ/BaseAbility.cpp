// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAbility.h"

ABaseAbility::ABaseAbility()
{
	PrimaryActorTick.bCanEverTick = true;

}
void ABaseAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ATori* ABaseAbility::getMyOwner()
{
	return myPlayer;
}

void ABaseAbility::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			
		}
	}
}

