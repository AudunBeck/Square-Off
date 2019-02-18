// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tori.h"
#include "BaseElement.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

UCLASS()
class UN_EZ_API ABaseAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual ATori* getMyOwner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATori* myPlayer;
};
