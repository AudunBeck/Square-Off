// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "WindElementAbility1.h"
#include "WindElementAbility2.h"
#include "GameFramework/Actor.h"
#include "WindElement.generated.h"

UCLASS()
class UN_EZ_API AWindElement : public ABaseElement
{
	GENERATED_BODY()

public:
	AWindElement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void ability1()override;
	virtual void ability2()override;
	virtual int returnElementType()override;

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility1> WindElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility2> WindElementAbility2_BP;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 5.0f;

	// How far ahead of Tori the ability spawns
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 100.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float boltSpeed = 3000.0f;

	bool chargingAbilit1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCharge = 2;
	
	// Charge that starts when you press attack, and fires the bolt when reaching 0
	float windUpTime;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxWindUpTime = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1damage = 30.f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float range = 400.f;


	// Ability 2 

	///Value not used
	/*UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;*/
	
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius0 = 60.0f;
	
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius1 = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius2 = 600.0f;
	
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius3 = 900.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float timeTilSecond = 2.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float timeTilThird = 2.f;

	// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage1 = 30.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage2 = 50.f;

	int windChi;
	float buffDur;
	float maxBuffDur;
	bool chargingAbilit2;
};
