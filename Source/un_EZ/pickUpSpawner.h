// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "pickUp.h"
#include "pickUpSpawner.generated.h"

UCLASS()
class UN_EZ_API ApickUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ApickUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "PickUps")
		TSubclassOf<class ApickUp> ElementToSpawn;
	UPROPERTY(VisibleAnywhere, Category = "PickUps")
		ApickUp* SpawnedElement;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "PickUps")
		float timeBetweenPickUps;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PickUps")
		void elementPickedUp();

	UFUNCTION(BlueprintCallable, Category = "PickUps")
		void spawnElement();

};
