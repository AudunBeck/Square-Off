// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElement.h"

void ARockElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (charging)
	{
		chargeFloat += DeltaTime;
		if (chargeFloat >= maxCharge)
		{
			chargeFloat = maxCharge;
			ability1End();

		}

	}

}

void ARockElement::ability1()
{
	if (ammo1 > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("RockElement Ability 1 firing"));
		charging = true;
		myOwner->setMoveSpeed(0.f);
		myOwner->currentSpeed = 0;
		chargeFloat = 0;
	}
	Super::ability1();
}

void ARockElement::ability1End()
{
	if (charging)
	{
		ARockElementAbility1* temp;
		temp = GetWorld()->SpawnActor<ARockElementAbility1>(RockElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation());
		temp->setupAttack(myOwner, ability1lifeSpan, ability1Range, chargeFloat);
		myOwner->setMoveSpeed(myOwner->moveSpeed);
		myOwner->currentSpeed = myOwner->moveSpeed;
		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * rockPunch * chargeFloat, false, true);
	}
	charging = false;
	
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
		ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(RockElementAbility2_BP, newVec, playerRot);
		temp->setupAttack(myOwner, ability2Scale, ability2Lifespan, ability2Speed);
	}

	Super::ability2();
}
