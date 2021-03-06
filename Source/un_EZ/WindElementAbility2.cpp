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
	knockback = myElement->ability2KnockBack;
	damage = myElement->ability2Damage;
	radius = myElement->ability2Radius;
	this->SetLifeSpan(myElement->ability2Lifespan);
	myElement->windUsingAbility2 = true;

	myPlayer->setMoveSpeed(myPlayer->moveSpeed + myElement->bonusSpeed);
	myPlayer->GetCharacterMovement()->GravityScale = myElement->ability2Gravity;
	stopCollision();
}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWindElementAbility2::startCollision()
{
	myElement->windUsingAbility2 = false;
	myPlayer->setMoveSpeed(myPlayer->moveSpeed);
	myPlayer->GetCharacterMovement()->GravityScale = 4.f;
	checkForEnemies();
}

void AWindElementAbility2::checkForEnemies()
{
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
					// Calculates the distance from impact point, to the enemy its checking
					tempLocation = myPlayer->GetActorLocation();
					enemyLocation = enemyReference->GetActorLocation();
					radiusToEnemy = sqrt(pow((enemyLocation.Y - tempLocation.Y), 2) + pow((enemyLocation.Z - tempLocation.Z), 2));
					if (radiusToEnemy < radius)
					{
						FVector knockDirection = (enemyLocation - tempLocation);
						knockDirection.Normalize();
						enemyReference->recieveDamage(myPlayer, damage, knockback, myPlayer->GetActorLocation());
					}
				}
			}
		}
	}
}

