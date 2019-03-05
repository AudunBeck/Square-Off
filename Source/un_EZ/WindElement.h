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

	// Ability 1
		///Value not used
	/*UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;*/

		// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float MaxAbility1Damage = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxDistance = 700.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float channelSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxChannelTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxInterval = 0.2f;

	float interval;
	float ability2Damage;
	float distance;
	float channelTime;

	// Ability 2 


};
