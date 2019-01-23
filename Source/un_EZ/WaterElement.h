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
		float boltSpeedBuffed = 2200.0f;

	bool charging;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCharge = 2;
	// Charge that starts when you press attack, and fires the bolt when reaching 0
	float windUpTime;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxWindUpTime = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float damage = 30.f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float damageBuffed = 60.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ccDur = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ccDurBuffed = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float slow = 15.f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float slowBuffed = 30.f;
	
	int counter = 0;


	// Ability 2
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.f;
	float buffDur;
	float maxBuffDur;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float dashDist = 3000;

	// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage = 0.f;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2CcDur = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Slow = 30.f;

};
