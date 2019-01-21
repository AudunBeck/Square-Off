// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseElement.h"
#include "RockElementAbility2.h"
#include "RockElement.generated.h"

/**
 * 
 */
UCLASS()
class UN_EZ_API ARockElement : public ABaseElement
{
	GENERATED_BODY()

public:

	virtual void ability1()override;
	virtual void ability2()override;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Range;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		FVector ability2Scale;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Lifespan = 2;
	


	UPROPERTY(EditAnywhere)
		TSubclassOf<class ARockElementAbility2> wallBlueprint;
	
};
