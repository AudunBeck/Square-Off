// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "WaterElementAbility1.h"
#include "WaterElementAbility2.h"
#include "GameFramework/Actor.h"
#include "WaterElement.generated.h"

UCLASS()
class UN_EZ_API AWaterElement : public ABaseElement
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ability1()override;
	virtual void ability2()override;

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWaterElementAbility1> WaterElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWaterElementAbility2> WaterElementAbility2_BP;

	// Ability 1
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 100.f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float boltSpeed = 1200.0f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		bool charging;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCharge = 2;
	// Charge that starts when you press attack, and fires the bolt when reaching 0
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float windUpTime;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxWindUpTime = 0.3f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float damage = 30.f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ccDur = 1.5f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float slow = 20.f;



	// Ability 2
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Range;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		FVector ability2Scale;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Lifespan = 2;

};
