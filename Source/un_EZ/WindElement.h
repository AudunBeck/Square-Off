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

	// Ability 1
		///Value not used
	/*UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;*/

		// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float MaxAbility1Damage = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float channelSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxChannelTime = 1.2f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxInterval = 0.4f;

	float interval;
	float ability2Damage;
	float distance;
	float channelTime;

	// Ability 2 
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float buffDur = 2.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float bonusSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float pushForce = 300.f;

};
