// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseElement.h"
#include "Tori.h"

ABaseElement::ABaseElement()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseElement::BeginPlay()
{
	Super::BeginPlay();

	ammo1 = maxAmmo1;
	ammo2 = maxAmmo2;
	cooldownAbility1 = maxCooldownAbility1;
	cooldownAbility2 = maxCooldownAbility2;
	myOwner = Cast<ATori>(GetOwner());
}

void ABaseElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (myOwner != nullptr)
		SetActorLocation(myOwner->GetActorLocation());

	if (ammo1 < maxAmmo1)
	{
		cooldownAbility1 -= DeltaTime;
		if (cooldownAbility1 <= 0)
		{
			ammo1 += ammoPerCd1;
			if (ammo1 > maxAmmo1)
				ammo1 = maxAmmo1;

			cooldownAbility1 = maxCooldownAbility1;
		}
	}

	if (ammo2 < maxAmmo2)
	{
		cooldownAbility2 -= DeltaTime;
		if (cooldownAbility2 <= 0)
		{
			ammo2 += ammoPerCd2;
			if (ammo2 > maxAmmo2)
				ammo2 = maxAmmo2;
			cooldownAbility2 = maxCooldownAbility2;
		}

	}		
}

void ABaseElement::setPlayer(class ATori * newOwner)
{
	myOwner = newOwner;
}

ATori * ABaseElement::getMyOwner()
{
	if (myOwner == nullptr)
		return nullptr;
	else
		return myOwner;
}

void ABaseElement::ability1()
{
	if (ammo1 > 0)
	{
		ammo1 -= 1;
		ability1Anim();
	}
}

void ABaseElement::ability1FireCode()
{
}

void ABaseElement::ability1End()
{

}

int ABaseElement::returnElementType()
{
	return 0;
}

void ABaseElement::ability2()
{
	if (ammo2 > 0)
	{
		ammo2 -= 1;
		ability2Anim();
	}
}

void ABaseElement::ability2FireCode()
{
}

void ABaseElement::ability2End()
{
	myOwner->ability2Used = false;
}

int ABaseElement::switchToElement(bool active)
{
	setActive(active);
	isActive = active;
	return elementType;
}