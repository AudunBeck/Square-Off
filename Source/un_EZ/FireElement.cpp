// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElement.h"

void AFireElement::ability1()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 1 firing"));

	// Dash part of the attack
	if (ammo1 > 0)
	{
		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * firePunch, false, true);
		AFireElementAbility1* temp;
		temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP,
			myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation());
		if (fireChi > 0)
		{
			temp->setupAttack(myOwner, ability1lifeSpan, ability1Range, boostedAbility1Scale);
			fireChi -= 1;
		}
		else
		{
			temp->setupAttack(myOwner, ability1lifeSpan, ability1Range, FVector(1, 1, 1));
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


		AFireElementAbility2* temp;
		temp = GetWorld()->SpawnActor<AFireElementAbility2>(FireElementAbility2_BP,
			myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability2Range, myOwner->GetActorRotation());

		temp->setupAttack(myOwner, ability1lifeSpan, ability2Range);

		// Refills ammo1 as mentioned in design doc
		ammo1 += ammo1Refill;
		if (ammo1 > maxAmmo1)
			ammo1 = maxAmmo1;
		fireChi = maxFireChi;
	}
	Super::ability2();
}
