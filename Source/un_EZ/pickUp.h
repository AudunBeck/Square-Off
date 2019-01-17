// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "BaseElement.h"
#include "pickUp.generated.h"

UCLASS()
class UN_EZ_API ApickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ApickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USphereComponent* collider;

	UPROPERTY(EditAnywhere, Category = "Element")
		TSubclassOf<class ABaseElement> ElementBlueprint;

};
