// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "CameraSetUp.generated.h"

UCLASS()
class UN_EZ_API ACameraSetUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraSetUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "SpringArm")
		float minArmLength; 
	UPROPERTY(EditAnywhere, Category = "SpringArm")
		float maxArmLength;
	UPROPERTY(EditAnywhere, Category = "SpringArm")
		FVector offsetCam;
	UPROPERTY(EditAnywhere, Category = "SpringArm")
		float spawnerOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* StageCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<APlayerController*> playerControllers;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FVector>pawnLocations;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector centerLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float furthestPawn;

	bool test = false;
	void findPlayerControllers();
	void getPawnLocations();
	void calculateCenterLocation();
	void setCameraPosition();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CameraVariables")
		int playerAmount = 0;
};
