// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElement.h"

void AFireElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;

	if (shouldDash)
	{
		if ((attackTime + dashTime) < currentTime)
		{
			FVector newLocation = myOwner->GetActorLocation();
			newLocation += myOwner->GetActorForwardVector() * fireDash;
			myOwner->SetActorLocation(newLocation);
		}
		else
		{
			shouldDash = false;
		}
		
	}
}

void AFireElement::ability1()
{
	UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 1 firing"));

	// Dash part of the attack

	//FVector NewLocation = GetActorLocation();
	//NewLocation += myOwner->GetActorForwardVector() * fireDash;
	//myOwner->SetActorLocation(NewLocation);
	
	shouldDash = true;
	dashTime = 0.5;
	attackTime = currentTime;

	AFireElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP, myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * 100.f, myOwner->GetActorRotation());
	temp->setupAttack(myOwner, ability1lifeSpan);
}

void AFireElement::ability2()
{
	FVector forwardVec = myOwner->GetActorForwardVector();
	FVector playerVec = myOwner->GetActorLocation();
	FRotator playerRot = myOwner->GetActorRotation();
	const FVector newVec = (forwardVec * ability2Range) + playerVec;

	UE_LOG(LogTemp, Warning, TEXT("FireElement Ability 2 firing"));
	AFireElementAbility2* temp = GetWorld()->SpawnActor<AFireElementAbility2>(FireElementAbility2_BP, newVec, playerRot);
	temp->setupAttack(myOwner, ability2Lifespan);

}
