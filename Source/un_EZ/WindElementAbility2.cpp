// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"

AWindElementAbility2::AWindElementAbility2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	//collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility2::OnOverlapBegin);
	
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();

}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;
	checkForEnemy();
}

void AWindElementAbility2::setupAttack(ATori * newOwner, AWindElement * myElementIn, float damageIn, float outerRadiusIn)
{
	myPlayer = newOwner;
	myElement = myElementIn;
	SetLifeSpan(myElement->ability2lifeSpan);
	damage = damageIn;
	innerRadius = myElement->innerRadius;
	outerRadius = outerRadiusIn;
	//collider->SetSphereRadius(outerRadius);
}

void AWindElementAbility2::checkForEnemy()
{
	enemyReference = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATori::StaticClass(), enemy);
	numOfEnemy = enemy.Num() -1;
	if (numOfEnemy > 0)
	{
		for (int i = 0; i <= numOfEnemy; i++)
		{
			playerLocation = myPlayer->GetActorLocation();
			enemyReference = Cast<ATori>(enemy[i]);
			enemyLocation = enemyReference->GetActorLocation();
			RadiusToEnemy = sqrt(pow((enemyLocation.X - playerLocation.X), 2) + pow((enemyLocation.Y - playerLocation.Y), 2));
			if (RadiusToEnemy < outerRadius && RadiusToEnemy > innerRadius)
			{
				pushDirection = (enemyLocation - playerLocation);

				if (myElement->counter == 1)
				{
					UE_LOG(LogTemp, Error, TEXT("Counter is: %i"), myElement->counter);
					enemyReference->recieveDamage(myElement->ability2Damage1);
				}

				if (myElement->counter == 2)
				{
					UE_LOG(LogTemp, Error, TEXT("Counter is: %i"), myElement->counter);
					enemyReference->LaunchCharacter(pushDirection, true, true);
				}

				if (myElement->counter == 3)
				{
					UE_LOG(LogTemp, Error, TEXT("Counter is: %i"), myElement->counter);
					enemyReference->LaunchCharacter(pushDirection, true, true);
					enemyReference->recieveDamage(myElement->ability2Damage2);
				}
			}
		}
	}


}
