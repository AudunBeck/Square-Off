// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "FireElementAbility1.h"
#include "FireElementAbility2.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "FireElement.generated.h"


UCLASS()
class UN_EZ_API AFireElement : public ABaseElement
{
	GENERATED_BODY()
	
public:	

	AFireElement();

	virtual void ability1()override;
	virtual void ability2()override;

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AFireElementAbility1> FireElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AFireElementAbility2> FireElementAbility2_BP;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float firePunch = 3000;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Damage;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1BuffedDamage;


	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Range;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int ammo1Refill = 2;

	/// Add a function that reads how long the dash lasts, and constantly update the lifespan accordingly
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Lifespan = 2;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float fireKick = 6000;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		int maxFireChi = 2;

	int fireChi;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		FVector boostedAbility1Scale;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage;
	
	UDataTable* BalancingTable;
};
