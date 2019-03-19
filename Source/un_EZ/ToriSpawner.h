// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "ToriSpawner.generated.h"

UCLASS()
class UN_EZ_API AToriSpawner : public APawn
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

	UPROPERTY(EditAnywhere, Category = "Spawning Player")
		float dropSpeed = 10;
	UPROPERTY(EditAnywhere, Category = "Spawning Player")
		float directionSpeed = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Player")
		UBoxComponent* Collider;
	bool moving = false;
	FVector direction;

	void moveDirection(float AxisValue);

};
