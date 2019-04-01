// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraSetUp.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values
ACameraSetUp::ACameraSetUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	StageCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("StageCamera"));
	StageCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACameraSetUp::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ACameraSetUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!test)
	{
		findPlayerControllers();
		test = true;
	}
	getPawnLocations();
	calculateCenterLocation();
	setCameraPosition();

}

void ACameraSetUp::findPlayerControllers()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		playerControllers.Add(Iterator->Get());
	}
	UE_LOG(LogTemp, Warning, TEXT("Found %i players"), playerControllers.Num());
	pawnLocations.SetNum(playerControllers.Num());

}

void ACameraSetUp::getPawnLocations()
{

	for (int i = 0; i < pawnLocations.Num(); i++)
	{
		if (playerControllers[i]->GetPawn() != nullptr)
		{
			pawnLocations[i] = playerControllers[i]->GetPawn()->GetActorLocation();			
		}
		else if(logbug) //This is only here to please the UE4 math gods, they want a UE_LOG sacrifice
		{
			UE_LOG(LogTemp, Warning, TEXT("Removed player at %i"), i);
			logbug = false;
		}
	}
}

void ACameraSetUp::calculateCenterLocation()
{
	furthestPawn = 0;
	int numberOfPawns = pawnLocations.Num();
	centerLocation = FVector();
	for (int i = 0; i < numberOfPawns; i++)
	{
		centerLocation.Y += pawnLocations[i].Y;
		centerLocation.Z += pawnLocations[i].Z;
	}
	centerLocation.X = 0;


	centerLocation = (centerLocation / numberOfPawns) + offsetCam;


	for (int i = 0; i < pawnLocations.Num(); i++)
	{
		FVector tempVector = centerLocation - pawnLocations[i];
		float tempFloat = tempVector.Size();
		if (furthestPawn < tempFloat)
			furthestPawn = tempFloat;
		
	}
	//UE_LOG(LogTemp, Warning, TEXT("Furthest pawn %s"), furthestPawn);
}

void ACameraSetUp::setCameraPosition()
{
	SetActorLocation(centerLocation);
	float newArmLength = FMath::Clamp(furthestPawn, minArmLength, maxArmLength);
	SpringArm->TargetArmLength = newArmLength;
}

