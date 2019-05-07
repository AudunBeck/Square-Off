// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraSetUp.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "ToriSpawner.h"


//This actor contains a camera and follows up to 4 actors that are controlled by up to 4 player controllers,
//getting the locations from each of them and calculating a center position
//it then finds the furthes away actor and adjusts the length of the spring arm so all of the characters are on screen.

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
	if (!winningCam)
	{
		if (test)
		{
			getPawnLocations();
			calculateCenterLocation();
			setCameraPosition(DeltaTime);
		}
		else
		{
			findPlayerControllers();
			test = true;
			getPawnLocations();
			calculateCenterLocation();
			SetActorLocation(centerLocation);
		}
	}
	else
	{
		winCamPos(DeltaTime);
		calculateCenterLocation();
		setCameraPosition(DeltaTime);

	}


}

void ACameraSetUp::findPlayerControllers()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (Iterator.GetIndex() < playerAmount)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(Iterator.GetIndex()));
			playerControllers.Add(Iterator->Get());
		}
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(playerControllers.Num()));
	UE_LOG(LogTemp, Warning, TEXT("Found %i players"), playerControllers.Num());
	pawnLocations.SetNum(playerControllers.Num());

}

void ACameraSetUp::getPawnLocations()
{

	for (int i = 0; i < pawnLocations.Num(); i++)
	{
		if (playerControllers[i]->GetPawn() != nullptr)
		{
			AActor* player = playerControllers[i]->GetPawn();
			pawnLocations[i] = player->GetActorLocation();
			if (player->IsA(AToriSpawner::StaticClass()))
			{
				pawnLocations[i].Z -= spawnerOffset;
			}
		}
	}
}

void ACameraSetUp::calculateCenterLocation()
{
	furthestPawn = 0;
	int numberOfPawns = pawnLocations.Num();
	centerLocation = FVector(0.f, 0.f, 0.f);
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

void ACameraSetUp::setCameraPosition(float DeltaTime)
{

	FVector newLocation = centerLocation - GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("newLocation %s"), *newLocation.ToString());
	newLocation = newLocation.GetClampedToMaxSize(DeltaTime * maxCameraChange);
	SetActorLocation(GetActorLocation() + newLocation);
	float newArmLength = FMath::Clamp(furthestPawn, minArmLength, maxArmLength);
	SpringArm->TargetArmLength = newArmLength;
}

void ACameraSetUp::winningPlayer(int winner)
{
	playerWon = winner;
	winningCam = true;
}

void ACameraSetUp::winCamPos(float DeltaTime)
{
	FVector overrideLocation(0, 0, 0);
	if (playerControllers[playerWon]->GetPawn() != nullptr)
	{
		AActor* player = playerControllers[playerWon]->GetPawn();
		overrideLocation = player->GetActorLocation();
	}
	for (int i = 0; i < pawnLocations.Num(); i++)
	{
		pawnLocations[i] = overrideLocation;
	}
	if (minArmLength > 200)
	{
		minArmLength -= DeltaTime * maxCameraChange;
		if (minArmLength < 200)
			minArmLength = 200;
	}
}

