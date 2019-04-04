// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElement.h"
#include "ConstructorHelpers.h"
#include "WaterElementStruct.h"

// Sets default values
AWaterElement::AWaterElement()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable>
		WaterElementTable(TEXT("DataTable'/Game/DataTables/WaterElementTable.WaterElementTable'"));
	BalancingTable = WaterElementTable.Object;

	//Searching and getting data
	FWaterElementStruct* Ability1Data = BalancingTable->FindRow<FWaterElementStruct>(FName("1"), FString(""));
	FWaterElementStruct* Ability2Data = BalancingTable->FindRow<FWaterElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		damage = Ability1Data->Damage;
		maxCharge = Ability1Data->MaxCharge;
		maxCooldownAbility1 = Ability1Data->MaxCooldown;
		maxAmmo1 = Ability1Data->MaxAmmo;
		ammoPerCd1 = Ability1Data->AmmoPerCD;
		ability1Range = Ability1Data->Range;
		ability1lifeSpan = Ability1Data->LifeSpan;
		slow = Ability1Data->Slow;
		ccDur = Ability1Data->SlowDur;
		boltSpeed = Ability1Data->BoltSpeed;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		maxCooldownAbility2 = Ability2Data->MaxCooldown;
		maxAmmo2 = Ability2Data->MaxAmmo;
		ammoPerCd2 = Ability2Data->AmmoPerCD;
		ability2lifeSpan = Ability2Data->LifeSpan;
		ability2Slow = Ability2Data->Slow;
		ability2CcDur = Ability2Data->SlowDur;
		dashDist = Ability2Data->CounterDash;
	}
}

void AWaterElement::BeginPlay()
{
	Super::BeginPlay();
}

void AWaterElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 1
	//if (windUpTime > 0)
	//	windUpTime -= DeltaTime;

	//if (windUpTime <= 0 && charging == true)
	//{
	//	windUpTime = maxWindUpTime;
	//	myOwner->setRotationRate(0.f);
	//	myOwner->setMoveSpeed(myOwner->moveSpeed * 0.8);
	//	///Go over this to fix later.
	//	//Cast waterbolt

	//}

	// Ability 2
	if (buffDur >= 0)
	{
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		buffDur -= DeltaTime;
		if (buffDur <= 0)
		{
			myOwner->setMoveSpeed(myOwner->moveSpeed);
			myOwner->damageMultiplier = 1;

			// Starts collision towards other Tori's
			//startCollision();
		}
	}
}

void AWaterElement::ability1()
{
	//if (myOwner->ability1Ended == false)
	{
		Super::ability1();
		combo = !combo;
	}
}

void AWaterElement::ability1FireCode()
{
	// Does nothing

	myOwner->setRotationRate(myOwner->rotationRate);
	myOwner->setMoveSpeed(myOwner->moveSpeed);
	//Cast waterbolt
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AWaterElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AWaterElementAbility1>(WaterElementAbility1_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);


}

void AWaterElement::ability1End()
{

}

void AWaterElement::ability2()
{
	//if (myOwner->ability2Ended == false)
	{
		Super::ability2();
		myOwner->hitAnimImmune = true;
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		myOwner->currentSpeed = 0.f;
		buffDur = ability2lifeSpan;
	}

}

void AWaterElement::ability2FireCode()
{
	//FActorSpawnParameters tempParam;
	//tempParam.Owner = this;
	//AWaterElementAbility2* temp;
	///// Under "myPlayer->GetActorLocation() + myPlayer->GetActorFowardVector()," add spawnpoint to socket in the hand
	//temp = GetWorld()->SpawnActor<AWaterElementAbility2>(WaterElementAbility2_BP,
	//	myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);
}

void AWaterElement::ability2End()
{

}

void AWaterElement::outputLog()
{
	UE_LOG(LogTemp, Warning, TEXT("Collision on"));
}

int AWaterElement::returnElementType()
{
	Super::returnElementType();
	return 3;
}

void AWaterElement::ability2Counter_Implementation(ATori * enemy)
{
	//FVector enemyLocation = enemy->GetActorLocation();
	FVector ownerLocation = myOwner->GetActorLocation();
	FVector launchDirection = myOwner->GetActorForwardVector() * -1;
	myOwner->LaunchCharacter(launchDirection * dashDist, false, true);
	enemy->recieveDamage(myOwner, ability2Damage, ccDur, slow, 0);
	myOwner->setMoveSpeed(myOwner->moveSpeed);
	myOwner->hitAnimImmune = false;
	Countering = false;
}