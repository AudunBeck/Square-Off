// Fill out your copyright notice in the Description page of Project Settings.

#include "ToriSpawner.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"


// Sets default values
AToriSpawner::AToriSpawner()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
}

// Called when the game starts or when spawned
void AToriSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AToriSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Might need to rewrite, very patchy, just testing.
	FVector newLocation = GetActorLocation();
	newLocation += direction * dropSpeed;
	SetActorLocation(newLocation);
}

// Called to bind functionality to input
void AToriSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Move_Y", this, &AToriSpawner::moveDirection);
}

void AToriSpawner::moveDirection(float AxisValue)
{
	moving = true;
	direction = FVector(0, AxisValue, -1);
}

