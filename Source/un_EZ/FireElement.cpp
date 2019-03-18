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
		maxAmmo1 = Ability1Data->MaxAmmo;
		ammo1 = maxAmmo1;
		ammoPerCd1 = Ability1Data->AmmoPerCD;
		ability1Range = Ability1Data->Range;
		firePunch = Ability1Data->MoveRange;
		ability1lifeSpan = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		maxCooldownAbility2 = Ability2Data->MaxCooldown;
		maxAmmo2 = Ability2Data->MaxAmmo;
		ammo2 = maxAmmo2;
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
	if (myOwner->ability1Ended == false)
	{
		Super::ability1();
		UE_LOG(LogTemp, Warning, TEXT("Fire attack1"));
	}
}

void AFireElement::ability1FireCode()
{
	abilityHit = false;

	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AFireElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);

	if (!abilityHit)
		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * firePunch, false, true);
}

void AFireElement::ability1End()
{

}

void AFireElement::ability2()
{
	if (myOwner->ability2Ended == false)
	{
		Super::ability2();
		myOwner->locked = true;
		myOwner->setMoveSpeed(0);
	}
}

void AFireElement::ability2FireCode()
{	///Had to put rotationRate change here, seemed to go off after we changed it to the right value in the firelemenent hitting.
	/// multithreading???
	myOwner->setRotationRate(0);
	abilityHit = false;

	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AFireElementAbility2* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility2>(FireElementAbility2_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability2Range, myOwner->GetActorRotation(), tempParam);
	if (!abilityHit)
		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * fireKick, false, true);
}

void AFireElement::ability2End()
{

}

int AFireElement::returnElementType()
{
	Super::returnElementType();
	return 2;
}

void AFireElement::BeginPlay()
{
	Super::BeginPlay();
	attachFireEmitters();
}
