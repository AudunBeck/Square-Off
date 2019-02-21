// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"

AWindElementAbility2::AWindElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	myWindChi = myElement->windChi;
	switch(myWindChi)
	{
		case 0:
			SetLifeSpan(myPlayer->globalCooldown);
			break;
		case 1:
			SetLifeSpan(myElement->timeTilSecond);
			break;
		case 2:
			SetLifeSpan(myElement->timeTilSecond + myElement->timeTilThird);
			break;
	}
	counter = 0;
}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(counter == 0)
		firstWave();

	if (counter == 1 && (GetGameTimeSinceCreation() > myElement->timeTilSecond) && myWindChi >= 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempting to shoot second wave"));
		secondWave();
	}
		

	if (counter == 2 && (GetGameTimeSinceCreation() > myElement->timeTilSecond + myElement->timeTilThird) && myWindChi == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempting to shoot third wave"));
		thirdWave();
	}
}

// Checks for enemies, and affect them
void AWindElementAbility2::checkForEnemy(float innerRadius, float outerRadius)
{
	enemyReference = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATori::StaticClass(), enemy);
	numOfEnemy = enemy.Num() -1;
	if (numOfEnemy > 0)
	{
		for (int i = 0; i <= numOfEnemy; i++)
		{
			enemyReference = Cast<ATori>(enemy[i]);

			playerLocation = myPlayer->GetActorLocation();			
			enemyLocation = enemyReference->GetActorLocation();
			pushDirection = (enemyLocation - playerLocation);

			RadiusToEnemy = sqrt(pow((enemyLocation.X - playerLocation.X), 2) + pow((enemyLocation.Y - playerLocation.Y), 2));
			if (RadiusToEnemy > innerRadius && RadiusToEnemy < outerRadius)
			{
				switch (counter)
				{
					case 0:
						enemyReference->recieveDamage(myElement->ability2Damage1);
						break;
					case 1:
						enemyReference->LaunchCharacter(pushDirection, true, true);
						break;
					case 2:
						enemyReference->recieveDamage(myElement->ability2Damage1);
						enemyReference->LaunchCharacter(pushDirection, true, true);
						break;
				}
			}
		}
	}
}

void AWindElementAbility2::firstWave()
{
	checkForEnemy(myElement->radius0, myElement->radius1);
	counter = 1;
}

void AWindElementAbility2::secondWave()
{
	checkForEnemy(myElement->radius1, myElement->radius2);
	counter = 2;
}

void AWindElementAbility2::thirdWave()
{
	checkForEnemy(myElement->radius2, myElement->radius3);
}

