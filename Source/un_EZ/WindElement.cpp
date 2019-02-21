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
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	if (windUpTime > 0)
		windUpTime -= DeltaTime;

	if (windUpTime <= 0 && chargingAbilit1 == true)
	{
		//Cast windbolt
		AWindElementAbility1* temp;
		/// Under "myOwner->GetActorLocation() + myOwner->GetActorFowardVector()," add spawnpoint to socket in the hand
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);

		UE_LOG(LogTemp, Warning, TEXT("WindElement Ability 1 fired"));
		myOwner->setRotationRate(myOwner->rotationRate);
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		chargingAbilit1 = false;
	}

	// Ability 2
	if (buffDur > 0)
	{
		buffDur -= DeltaTime;
		if (buffDur <= 0 && chargingAbilit2 == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("WindElementAbility 2 buffduration is 0."));
			myOwner->locked = 0;
			myOwner->setMoveSpeed(myOwner->moveSpeed);
			chargingAbilit2 = false;
		}
	}
	// To allow maxBuffTime to be 0, else the if-statement over (if(buffDur > 0)) can't be true
	if (buffDur == 0 && chargingAbilit2 == true)
		chargingAbilit2 = false;

}


void AWindElement::ability1()
{
	if (ammo1 > 0 && chargingAbilit1 == false && myOwner->locked <= 0.f)
	{
		chargingAbilit1 = true;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 1 charging up"));
		windUpTime = maxWindUpTime;
		myOwner->setRotationRate(0.f);
		myOwner->setMoveSpeed(myOwner->moveSpeed * 0.8);
	}
	Super::ability1();
}

void AWindElement::ability2()
{
	if (ammo2 > 0 && chargingAbilit2 == false && myOwner->locked <= 0.f)
	{
		chargingAbilit2 = true;
		switch (windChi)
		{
		case 0:
			maxBuffDur = 0;
			break;
		case 1:
			maxBuffDur = timeTilSecond;
			break;
		case 2:
			maxBuffDur = timeTilThird + timeTilSecond;
			break;
		}
		buffDur = maxBuffDur;
		myOwner->locked = myOwner->globalCooldown;
		if(windChi != 0)
			myOwner->setMoveSpeed(myOwner->moveSpeed * 0.3); /// Add this to UPROPERTY if we decide to keep the slow effect while ability2 is active. Remove if not.

		
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has: %i, windChi."), windChi);
		AWindElementAbility2* temp;
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<AWindElementAbility2>(WindElementAbility2_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);
		windChi = 0;
		Super::ability2();
	}
	else if(ammo2 == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has no ammo"));
	}
	else if (chargingAbilit2 == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 is already being charged"));
	}
}

int AWindElement::returnElementType()
{
	Super::returnElementType();
	return 4;
}
