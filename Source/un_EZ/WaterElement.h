// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "WaterElementAbility1.h"
#include "WaterElementAbility2.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "WaterElement.generated.h"

UCLASS()
class UN_EZ_API AWaterElement : public ABaseElement
{
	GENERATED_BODY()

public:
	AWaterElement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void ability1()override;
	virtual void ability1FireCode()override;
	virtual void ability1End()override;

	virtual void ability2()override;
	virtual void ability2FireCode()override;
	virtual void ability2End()override;

	virtual int returnElementType()override;

	bool buffedAbility1;

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWaterElementAbility1> WaterElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWaterElementAbility2> WaterElementAbility2_BP;


	// Blueprint functions
	UFUNCTION(BlueprintCallable, Category = "Output Log WaterElement")
		void outputLog();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WaterElement collision")
		void startCollision();


	// Ability 1
	float windUpTime;
	bool charging;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 5.0f;

	// How far ahead of Tori the ability spawns
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 100.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float boltSpeed = 1200.0f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCharge = 2;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxWindUpTime = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float damage = 30.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ccDur = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float slow = 15.f;

	// Ability 2
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;

	UPROPERTY(BlueprintReadOnly)
		float buffDur = 0;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float dashDist = 3000;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage = 0.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2CcDur = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Slow = 30.f;

	UDataTable* BalancingTable;
};
