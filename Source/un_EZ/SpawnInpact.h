#pragma once

#include "CoreMinimal.h"
#include "Tori.h"
#include "GameFramework/Actor.h"
#include "SpawnInpact.generated.h"

UCLASS()
class UN_EZ_API ASpawnInpact : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnInpact();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void checkForEnemies(ATori* myPlayer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float inpactRadius = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float knockbackForce = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float knockbackTime = 1.f;

	FVector enemyLocation;
	FVector tempLocation;
	TArray<AActor*> foundEnemy;
	int numberOfEnemyFound;
	float radiusToEnemy;
};
