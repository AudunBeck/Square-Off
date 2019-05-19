// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraSetUp.h"
#include "Tori.h"
#include "UIHandler.generated.h"

UCLASS()
class UN_EZ_API AUIHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void getPlayers();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACameraSetUp* Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<float> playersHitPointPercent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int> playersScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float playerAmount;

};
