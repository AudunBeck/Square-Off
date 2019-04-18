// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	ASpawnInpact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		void checkForEnemies(ATori* myPlayer);

	FVector enemyLocation;
	FVector tempLocation;
	TArray<AActor*> foundEnemy;
	int numberOfEnemyFound;
	float radiusToEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float inpactRadius = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float knockbackForce = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float knockbackTime = 1.f;
};
