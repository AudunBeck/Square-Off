// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElement.h"

void ARockElement::ability1()
{
	UE_LOG(LogTemp, Warning, TEXT("RockElement Ability 1 firing"));
	ARockElementAbility1* temp;
	temp = GetWorld()->SpawnActor<ARockElementAbility1>(RockElementAbility1_BP, myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * 100.f, myOwner->GetActorRotation());
	temp->setupAttack(myOwner, 0.1f);
}

void ARockElement::ability2()
{
	UE_LOG(LogTemp, Warning, TEXT("RockElement Ability 2 firing"));
}
