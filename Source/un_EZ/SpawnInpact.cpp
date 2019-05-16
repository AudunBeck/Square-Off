#include "SpawnInpact.h"
#include "Kismet/GameplayStatics.h"

ASpawnInpact::ASpawnInpact()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnInpact::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnInpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnInpact::checkForEnemies(ATori* myPlayer)
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
					tempLocation = GetActorLocation();
					enemyLocation = enemyReference->GetActorLocation();
					radiusToEnemy = sqrt(pow((enemyLocation.Y - tempLocation.Y), 2) + pow((enemyLocation.Z - tempLocation.Z), 2));
					if (radiusToEnemy < inpactRadius)
					{
						enemyReference->recieveDamage(myPlayer, damage);
						FVector knockDirection = (enemyLocation - tempLocation);
						knockDirection.Normalize();
						enemyReference->forceMove(knockDirection, knockbackForce, knockbackTime);
					}
				}
			}
		}
		this->Destroy();
	}
}