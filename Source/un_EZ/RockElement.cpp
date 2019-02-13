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
		myOwner->setMoveSpeed(myOwner->moveSpeed * 0.5f);
		myOwner->currentSpeed = myOwner->moveSpeed * 0.5f;
		chargeFloat = 0;
		myOwner->locked = maxCharge;
	}
	Super::ability1();
}

void ARockElement::ability1End()
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
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(RockElementAbility2_BP, newVec, playerRot, tempParam);
	}

	Super::ability2();
}
