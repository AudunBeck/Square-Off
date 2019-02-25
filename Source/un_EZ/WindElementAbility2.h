// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "WindElement.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility2.generated.h"

class AWindElement;
class ATori;

UCLASS()
class UN_EZ_API AWindElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()

public:
	AWindElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	int counter;
	int myWindChi;
	float currentTime;


	UPROPERTY(BlueprintReadWrite)
		class AWindElement* myElement;
	UPROPERTY(BlueprintReadWrite)
		class ATori* enemyReference;
	UPROPERTY(BlueprintReadWrite)
		float distToEnemy;
	UPROPERTY(BlueprintReadWrite)
		float dotValue;
	UPROPERTY(BlueprintReadWrite)
		float dotProduct;
	UPROPERTY(BlueprintReadWrite)
		float RadiusToEnemy;
	UPROPERTY(BlueprintReadWrite)
		FVector pushDirection;

	TArray <AActor*> enemy;
	int numOfEnemy;
	FVector playerLocation;
	FVector enemyLocation;
	FVector a;
	FVector b;

	void checkForEnemy(float innerRadius, float outerRadius);
	void firstWave();
	void secondWave();
	void thirdWave();

	USphereComponent* collider;
};
