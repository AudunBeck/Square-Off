// Fill out your copyright notice in the Description page of Project Settings.

#include "pickUp.h"

// Sets default values
ApickUp::ApickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = collider;
	collider->SetCollisionProfileName(TEXT("Pawn"));

}

// Called when the game starts or when spawned
void ApickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ApickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

