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
	virtual void ability2End()override;
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

	bool canChannel = false;

	///Value not used
	/*UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;*/

	// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float MaxAbility2Damage = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxDistance = 700.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float channelSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxChannelTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxInterval = 0.2f;

	float interval;
	float ability2Damage;
	float distance;
	float channelTime;
};
