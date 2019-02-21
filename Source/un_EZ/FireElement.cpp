// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElement.h"
#include "ConstructorHelpers.h"
#include "FireElementStruct.h"

AFireElement::AFireElement()
{

	static ConstructorHelpers::FObjectFinder<UDataTable>
		FireElementTable(TEXT("DataTable'/Game/DataTables/FireElementTable.FireElementTable'"));
	BalancingTable = FireElementTable.Object;
	//Searching and getting data

	FFireElementStruct* Ability1Data = BalancingTable->FindRow<FFireElementStruct>(FName("1"), FString(""));
	FFireElementStruct* Ability2Data = BalancingTable->FindRow<FFireElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		ability1Damage = Ability1Data->Damage;
		ability1BuffedDamage = Ability1Data->BuffedDamage;
		maxCooldownAbility1 = Ability1Data->MaxCooldown;
		ammo1 = Ability1Data->MaxAmmo;
		ammoPerCd1 = Ability1Data->AmmoPerCD;
		ability1Range = Ability1Data->Range;
		firePunch = Ability1Data->MoveRange;
		ability1lifeSpan = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		maxCooldownAbility2 = Ability2Data->MaxCooldown;
		ammo2 = Ability2Data->MaxAmmo;
		ammoPerCd2 = Ability2Data->AmmoPerCD;
		ability2Range = Ability2Data->Range;
		fireKick = Ability2Data->MoveRange;
		ability2Lifespan = Ability2Data->LifeSpan;
		maxFireChi = Ability2Data->FireChi;
		boostedAbility1Scale = Ability2Data->BuffedScale;
	}
}

void AFireElement::ability1()
{
	////UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 1 firing"));
	if (ammo1 > 0 && myOwner->ability1Ended == false)
	{
		Super::ability1();
	}

}

void AFireElement::ability1End()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 1 firing"));

// Dash part of the attack

	myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * firePunch, false, true);
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AFireElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);
}

void AFireElement::ability2()
{
	if (ammo2 > 0 && myOwner->ability2Ended == false)
	{
		Super::ability2();
	}

}

void AFireElement::ability2End()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 2 firing"));
	myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * fireKick, false, true);

	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AFireElementAbility2* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility2>(FireElementAbility2_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability2Range, myOwner->GetActorRotation(), tempParam);

	//temp->setupAttack(myOwner, ability1lifeSpan, ability2Range);

	// Refills ammo1 as mentioned in design doc
	ammo1 += ammo1Refill;
	if (ammo1 > maxAmmo1)
		ammo1 = maxAmmo1;
}

int AFireElement::returnElementType()
{
	Super::returnElementType();
	return 2;
}
