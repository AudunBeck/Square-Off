// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToriSpawner.generated.h"

UCLASS()
class UN_EZ_API AToriSpawner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AToriSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Player")
		float directionSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Player")
		float spawnHeight = 900.f;

	// How fast the spawner "falls" when it goes down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Player")
		float fallSpeed = 15.f;

	FVector direction;

	float inAxis;
	void moveDirection(float AxisValue);
	void spawnPlayer();
};
