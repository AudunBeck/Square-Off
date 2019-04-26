// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"
#include "Kismet/GameplayStatics.h"
#include "Tori.h"
#include "GameFramework/CharacterMovementComponent.h"

AWindElementAbility2::AWindElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;

}

AWindElementAbility2::~AWindElementAbility2()
{
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	this->SetLifeSpan(myElement->buffDur);
	//myPlayer->locked = true;
	myElement->windUsingAbility2 = true;

	myPlayer->setMoveSpeed(myPlayer->moveSpeed + myElement->bonusSpeed);
	myPlayer->GetCharacterMovement()->GravityScale = 2.f;
	
	// Stops collision towards other Tori's - Called in Blueprint
	stopCollision();
}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWindElementAbility2::startCollision()
{
	//myPlayer->locked = false;
	myElement->windUsingAbility2 = false;
	myPlayer->setMoveSpeed(myPlayer->moveSpeed);
	myPlayer->GetCharacterMovement()->GravityScale = 4.f;
	checkForEnemies(myPlayer);
}

void AWindElementAbility2::checkForEnemies(ATori * myPlayer)
{
	//myElement->ability2PullAnim();
	ATori* enemyReference = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATori::StaticClass(), foundEnemy);
	numberOfEnemyFound = foundEnemy.Num() - 1;
	if (numberOfEnemyFound > 0)
	{
		for (int i = 0; i <= numberOfEnemyFound; i++)
		{
			enemyReference = Cast<ATori>(foundEnemy[i]);
			{
				if (enemyReference != myPlayer)
				{
					tempLocation = myPlayer->GetActorLocation();
					enemyLocation = enemyReference->GetActorLocation();
					radiusToEnemy = sqrt(pow((enemyLocation.Y - tempLocation.Y), 2) + pow((enemyLocation.Z - tempLocation.Z), 2));
					if (radiusToEnemy < radius)
					{
						enemyReference->recieveDamage(myPlayer, damage);
						FVector knockDirection = (tempLocation - enemyLocation);
						knockDirection.Normalize();
						enemyReference->LaunchCharacter(knockDirection * inpactKnockback, true, true);
						
					}
				}
			}
		}
	}
}

