// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseElement.h"

// Sets default values
ABaseElement::ABaseElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseElement::BeginPlay()
{
	Super::BeginPlay();

	ammo1 = maxAmmo1;
	ammo2 = maxAmmo2;
	cooldownAbility1 = maxCooldownAbility1;
	cooldownAbility2 = maxCooldownAbility2;
	myOwner = Cast<ATori>(GetOwner());
}

// Called every frame
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

			//UE_LOG(LogTemp, Warning, TEXT("Ammo1 is %i now"), ammo1);

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

			//UE_LOG(LogTemp, Warning, TEXT("Ammo2 is %i now"), ammo2);
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
		//myOwner->ability1Used = true;
		ammo1 -= 1;
		ability1Anim();
	}
	//UE_LOG(LogTemp, Warning, TEXT("BaseElement Ability 1 firing"));
}

void ABaseElement::ability1End()
{
	//myOwner->ability1Used = false;
	//ability1AnimEnd();
}

int ABaseElement::returnElementType()
{
	return 0;
}

void ABaseElement::ability2()
{
	if (ammo2 > 0)
	{
		myOwner->ability2Used = true;
		ammo2 -= 1;
		//ability2AnimStart();
	}
	//UE_LOG(LogTemp, Warning, TEXT("BaseElement Ability 2 firing"));
}

void ABaseElement::ability2End()
{
	myOwner->ability2Used = false;
	//ability2AnimEnd();
}

int ABaseElement::switchToElement()
{
	return elementType;
}


