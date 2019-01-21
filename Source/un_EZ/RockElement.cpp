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
	FVector forwardVec = myOwner->GetActorForwardVector();
	FVector playerVec = myOwner->GetActorLocation();
	FRotator playerRot = myOwner->GetActorRotation();
	const FVector newVec = (forwardVec * ability2Range) + playerVec;

	UE_LOG(LogTemp, Warning, TEXT("RockElement Ability 2 firing"));
	ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(wallBlueprint, newVec, playerRot);
	temp->SetActorScale3D(ability2Scale);
	temp->SetLifeSpan(ability2Lifespan);
}
