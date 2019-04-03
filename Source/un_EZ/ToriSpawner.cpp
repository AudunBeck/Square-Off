// Fill out your copyright notice in the Description page of Project Settings.

#include "ToriSpawner.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"


// Sets default values
AToriSpawner::AToriSpawner()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->AirControl = 1.f;
}

// Called when the game starts or when spawned
void AToriSpawner::BeginPlay()
{
	Super::BeginPlay();
	shouldSpawn = false;
}

// Called every frame
void AToriSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Might need to rewrite, very patchy, just testing.
	FVector newLocation = GetActorLocation();
	if(shouldSpawn == false)
		SetActorLocation(FVector{ 0.f, newLocation.Y, spawnHeight});
}

// Called to bind functionality to input
void AToriSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Move_Y", this, &AToriSpawner::moveDirection);
	InputComponent->BindAction("Ability_1", IE_Pressed, this, &AToriSpawner::spawnPlayer);
}

void AToriSpawner::moveDirection(float AxisValue)
{
	AddMovementInput(FVector(0.f, 1, 0.f), AxisValue);
	
}

void AToriSpawner::spawnPlayer()
{
	shouldSpawn = true;
}
