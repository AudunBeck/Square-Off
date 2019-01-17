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
	
}

// Called every frame
void ABaseElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseElement::setOwner(ATori * newOwner)
{
	owner = newOwner;
}

void ABaseElement::ability1()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseElement Ability 1 firing"));
}

void ABaseElement::ability2()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseElement Ability 2 firing"));
}

