// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElement.h"

void AFireElement::ability1()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 1 firing"));

	// Dash part of the attack
	myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * firePunch, false, true);
	AFireElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * 100.f, myOwner->GetActorRotation());

	temp->setupAttack(myOwner, ability1lifeSpan);
}

void AFireElement::ability2()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 2 firing"));
	myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * fireKick, false, true);

	
	AFireElementAbility2* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility2>(FireElementAbility2_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * 100.f, myOwner->GetActorRotation());

	temp->setupAttack(myOwner, ability1lifeSpan);
}
