// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElement.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "ConstructorHelpers.h"

AFireElement::AFireElement()
{
	UDataTable* BalancingTable;
	static ConstructorHelpers::FObjectFinder<UDataTable>
		FireElementTable(TEXT("DataTable'/Game/DataTables/FireElementTable.FireElementTable'"));
	BalancingTable = FireElementTable.Object;
	static const FString ContextString(TEXT("GENERAL"));	

}

void AFireElement::ability1()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 1 firing"));

	// Dash part of the attack
	if (ammo1 > 0)
	{
		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * firePunch, false, true);
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		AFireElementAbility1* temp;
		temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP,
			myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(),tempParam);
		if (fireChi > 0)
		{
			fireChi -= 1;
		}
	}
	Super::ability1();
}

void AFireElement::ability2()
{
	if (ammo2 > 0)
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
		fireChi = maxFireChi;
	}
	Super::ability2();
}
