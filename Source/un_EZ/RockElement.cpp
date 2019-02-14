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
	
	if (charging)
	{
		if (chargeFloat < maxCharge)
		{
			chargeFloat += DeltaTime;
			if (chargeFloat > maxCharge)
				chargeFloat = maxCharge;
		}
		// Old version
		//if (chargeFloat >= maxCharge)
		//{
		//	chargeFloat = maxCharge;
		//	ability1End();
		//}
	}
}

void ARockElement::ability1()
{
	// if the character has ended all animations of the punch, you are able to start a new punch.
	if (ammo1 > 0 && myOwner->ability1Ended == false)
	{
		//Old Version
		UE_LOG(LogTemp, Warning, TEXT("RockElement Ability 1 firing"));
		//charging = true;
		//myOwner->setMoveSpeed(0.f);
		//myOwner->currentSpeed = 0;
		//chargeFloat = 0;
		//myOwner->locked = maxCharge;
		
		

		if (myOwner->ability1Ended)
		{
			//myOwner->ability1Ended = false;
		}

		Super::ability1();
		
	}
	
}

void ARockElement::ability1Anim_Implementation()
{
	//myOwner->ability1Ended = true;
	//ARockElementAbility1* temp;
	//FActorSpawnParameters tempParam;
	//tempParam.Owner = this;
	//temp = GetWorld()->SpawnActor<ARockElementAbility1>(RockElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
	//	myOwner->GetActorRotation(), tempParam);
	//myOwner->setMoveSpeed(myOwner->moveSpeed);
	//myOwner->currentSpeed = myOwner->moveSpeed;
	//myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * rockPunch * chargeFloat, false, true);
	//myOwner->locked = 0;
	//chargeFloat = 0;
}

void ARockElement::ability1End() // Currently goes off after the animation, look at the blueprint of rock element for more info.
{
	if (charging)
	{
		myOwner->ability1Ended = true;
		ARockElementAbility1* temp;
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<ARockElementAbility1>(RockElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		myOwner->currentSpeed = myOwner->moveSpeed;
		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * rockPunch * chargeFloat, false, true);
		myOwner->locked = 0;
		chargeFloat = 0;
		Super::ability1End();
		
	}
	//charging = false;
	
	
}

void ARockElement::ability2()
{
	if (ammo2 > 0)
	{
		FVector forwardVec = myOwner->GetActorForwardVector();
		FVector playerVec = myOwner->GetActorLocation();
		FRotator playerRot = myOwner->GetActorRotation();
		const FVector newVec = (forwardVec * ability2Range) + playerVec;

		//UE_LOG(LogTemp, Warning, TEXT("RockElement Ability 2 firing"));
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(RockElementAbility2_BP, newVec, playerRot, tempParam);
	}

	Super::ability2();
}
