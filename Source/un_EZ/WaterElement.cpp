// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElement.h"
#include "ConstructorHelpers.h"
#include "WaterElementStruct.h"

// Sets default values
AWaterElement::AWaterElement()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
		damageBuffed = Ability1Data->DamageBuffed;
		maxCharge = Ability1Data->MaxCharge;
		maxCooldownAbility1 = Ability1Data->MaxCooldown;
		maxAmmo1 = Ability1Data->MaxAmmo;
		ammoPerCd1 = Ability1Data->AmmoPerCD;
		ability1Range = Ability1Data->Range;
		ability1lifeSpan = Ability1Data->LifeSpan;
		slow = Ability1Data->Slow;
		ccDur = Ability1Data->SlowDur;
		boltSpeed = Ability1Data->BoltSpeed;
		slowBuffed = Ability1Data->SlowBuffed;
		ccDurBuffed = Ability1Data->SlowDurBuffed;
		boltSpeedBuffed = Ability1Data->BoltSpeedBuffed;
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

	if (windUpTime <= 0 && charging == true)
	{
		//Cast waterbolt
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		AWaterElementAbility1* temp;
		/// Under "myPlayer->GetActorLocation() + myPlayer->GetActorFowardVector()," add spawnpoint to socket in the hand
		temp = GetWorld()->SpawnActor<AWaterElementAbility1>(WaterElementAbility1_BP,
			myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);

		if (counter > 0)
			buffedAbility1 = true;
		else
			buffedAbility1 = false;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 1 fired"));
		myOwner->setRotationRate(myOwner->rotationRate);
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		charging = false;
	}

	// Ability 2
	if (buffDur > 0)
	{
		//myOwner->SetActorEnableCollision(false);
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		buffDur -= DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("counter dur left: %f"),buffDur);
		if (buffDur <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stopping counter movespeed should be %f"), myOwner->moveSpeed);
			myOwner->setMoveSpeed(myOwner->moveSpeed);
			myOwner->damageMultiplier = 1;
			tempTimer = 0.2f;	// Delay after ability2 register an attack and the time it takes to dash
		}
	}
	if (tempTimer > 0)
	{
		tempTimer -= DeltaTime;
		//if (tempTimer <= 0.f)
			//myOwner->SetActorEnableCollision(true);
	}
}

void AWaterElement::ability1()
{
	if (ammo1 > 0 && charging == false && myOwner->locked <= 0.f)
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
		//myOwner->SetActorEnableCollision(false);
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		myOwner->currentSpeed = 0.f;
		myOwner->damageMultiplier = 0;
		buffDur = maxBuffDur;
		myOwner->locked = buffDur;
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 ammo: %i"), ammo2);
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		AWaterElementAbility2* temp;
		/// Under "myPlayer->GetActorLocation() + myPlayer->GetActorFowardVector()," add spawnpoint to socket in the hand
		temp = GetWorld()->SpawnActor<AWaterElementAbility2>(WaterElementAbility2_BP,
			myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);
		Super::ability2();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaterElement Ability 2 has no ammo"));
	}
}
