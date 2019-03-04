// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElement.h"
#include "ConstructorHelpers.h"
#include "RockElementStruct.h"

ARockElement::ARockElement()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		RockElementTable(TEXT("DataTable'/Game/DataTables/RockElementTable.RockElementTable'"));
	BalancingTable = RockElementTable.Object;
	//Searching and getting data

	FRockElementStruct* Ability1Data = BalancingTable->FindRow<FRockElementStruct>(FName("1"), FString(""));
	FRockElementStruct* Ability2Data = BalancingTable->FindRow<FRockElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		ability1Damage = Ability1Data->Damage;
		maxCharge = Ability1Data->MaxCharge;
		maxCooldownAbility1 = Ability1Data->MaxCooldown;
		maxAmmo1 = Ability1Data->MaxAmmo;
		ammoPerCd1 = Ability1Data->AmmoPerCD;
		ability1Range = Ability1Data->Range;
		rockPunch = Ability1Data->MoveRange;
		ability1lifeSpan = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		maxCooldownAbility2 = Ability2Data->MaxCooldown;
		maxAmmo2 = Ability2Data->MaxAmmo;
		ammoPerCd2 = Ability2Data->AmmoPerCD;
		ability2Range = Ability2Data->Range;
		ability2Speed = Ability2Data->MoveRange;
		ability2Lifespan = Ability2Data->LifeSpan;
		ability2KnockbackMulti = Ability2Data->KnockBack;
	}
}

void ARockElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cooldown > 0)
		cooldown -= DeltaTime;

	// Hold the charge
	if (channelingAbility1 == true)
	{
		/// Can still use ability2 while charging - fix this with animation
		//UE_LOG(LogTemp, Warning, TEXT("Rock ability charging"));
		if (chargeFloat < maxCharge)
		{
			//chargeFloat += DeltaTime;
			if (chargeFloat > maxCharge)
				chargeFloat = maxCharge;
		}
	}
	if (channelingAbility1 == false && chargeFloat > 0)
	{
		// Reset parameters if needed - Else remove this if-statement
	}
}

void ARockElement::ability1()
{
	// if the character has ended all animations of the punch, you are able to start a new punch.
	myOwner->damageMultiplier = damageReduction;
	myOwner->setMoveSpeed(myOwner->moveSpeed * slowFactor);
	myOwner->currentSpeed = myOwner->moveSpeed * slowFactor;
	myOwner->ability1Used = true;
	myOwner->hitAnimImmune = true;

	//Super::ability1();
}

void ARockElement::ability1FireCode()
{
	ARockElementAbility1* temp;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	temp = GetWorld()->SpawnActor<ARockElementAbility1>(RockElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
		myOwner->GetActorRotation(), tempParam);
	myOwner->setMoveSpeed(0);
	myOwner->currentSpeed = myOwner->moveSpeed;
	myOwner->setRotationRate(0);
	myOwner->damageMultiplier = 1;
	myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * rockPunch, false, true);
	myOwner->hitAnimImmune = false;
	//chargeFloat = 0;
}


void ARockElement::ability1End() // Currently goes off after the animation, look at the blueprint of rock element for more info.
{

	myOwner->ability1Ended = true;
	myOwner->ability1Used = false;
	//Super::ability1End();
}

void ARockElement::ability2()
{
	/// Can still use ability2 while charging - fix this with animation
	/// Can also use multiple walls
	if (myOwner->ability2Ended == false && cooldown <= 0)
	{
		cooldown = ability2Lifespan; // To avoid spamming of the wall
		Super::ability2();
		FVector forwardVec = myOwner->GetActorForwardVector();
		FVector playerVec = myOwner->GetActorLocation();
		FRotator playerRot = myOwner->GetActorRotation();
		const FVector newVec = (forwardVec * ability2Range) + playerVec;
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(RockElementAbility2_BP, newVec, playerRot, tempParam);
	}
}

void ARockElement::ability2FireCode()
{
	FVector forwardVec = myOwner->GetActorForwardVector();
	FVector playerVec = myOwner->GetActorLocation();
	FRotator playerRot = myOwner->GetActorRotation();
	const FVector newVec = (forwardVec * ability2Range) + playerVec;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(RockElementAbility2_BP, newVec, playerRot, tempParam);

}

void ARockElement::ability2End()
{
	// Does nothing
}

int ARockElement::returnElementType()
{
	Super::returnElementType();
	return 1;
}

void ARockElement::BeginPlay()
{
	Super::BeginPlay();
	attachRockGlove();
}
