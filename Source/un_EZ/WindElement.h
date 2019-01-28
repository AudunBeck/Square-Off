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
	// Sets default values for this actor's properties
	AWindElement();

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
		TSubclassOf<class AWindElementAbility1> WindElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility2> WindElementAbility2_BP;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 5.0f;

	// How far ahead of Tori the ability spawns
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 100.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float boltSpeed = 1200.0f;

	bool charging;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCharge = 2;
	
	// Charge that starts when you press attack, and fires the bolt when reaching 0
	float windUpTime;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxWindUpTime = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float damage = 30.f;

	// Ability 2
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius1Count = 30.0f;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius2Count = 60.0f;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float radius3Count = 90.0f;
	float buffDur;
	float maxBuffDur;

	// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage = 0.f;
	
	int counter = 1;

	float tempTimer;
};
