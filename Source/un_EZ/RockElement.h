// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "RockElementAbility1.h"
#include "RockElementAbility2.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "RockElement.generated.h"

UCLASS()
class UN_EZ_API ARockElement : public ABaseElement
{
	GENERATED_BODY()

public:

	ARockElement();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ability1()override;
	virtual void ability1Anim_Implementation();

	virtual void ability1End()override;

	virtual void ability2()override;



	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class ARockElementAbility1> RockElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class ARockElementAbility2> RockElementAbility2_BP;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 0.1f;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 100.f;
	UPROPERTY(BlueprintReadWrite, Category = "Ability1")
		bool charging = true;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCharge = 2;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float chargeFloat;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float rockPunch;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Damage;



	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Range;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		FVector ability2Scale;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Lifespan = 10;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Speed;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2KnockbackMulti = 2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage;

	UDataTable* BalancingTable;
};
