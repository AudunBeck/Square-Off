// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElementAbility2.h"
#include "WaterElement.h"

// Sets default values
AWaterElementAbility2::AWaterElementAbility2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaterElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (buffDur > 0)
	{
		buffDur -= DeltaTime;
	}

	if (buffDur <= 0)
	{
		myElement->buffActive = false;
		this->Destroy();
	}
}

void AWaterElementAbility2::setupAttack(AWaterElement* myElementIn, float buffDurIn)
{
	buffDur = buffDurIn;
	myElement = myElementIn;
}
void AWaterElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}