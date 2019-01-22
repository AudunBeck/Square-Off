// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "FireElementAbility1.h"
#include "FireElementAbility2.h"
#include "FireElement.generated.h"

UCLASS()
class UN_EZ_API AFireElement : public ABaseElement
{
	GENERATED_BODY()
	
public:	

	virtual void ability1()override;
	virtual void ability2()override;

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AFireElementAbility1> FireElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AFireElementAbility2> FireElementAbility2_BP;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float fireDash = 3000;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Range;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Lifespan = 2;

};
