// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tori.h"
#include "Engine/World.h"
#include "BaseElement.generated.h"

UCLASS()
class UN_EZ_API ABaseElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	int elementType = 0;

	bool isActive;

	// Setting Owner
	void setPlayer(class ATori* newOwner);

	UPROPERTY(EditAnywhere)
		class ATori* myOwner;
	ATori* getMyOwner();

	// Ability 1 variables.
	virtual void ability1();
	virtual void ability1End();

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCooldownAbility1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float cooldownAbility1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		int maxAmmo1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		int ammoPerCd1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		int ammo1;



	// Ability 2 variables.
	virtual void ability2();
	virtual void ability2End();

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxCooldownAbility2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float cooldownAbility2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int maxAmmo2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int ammoPerCd2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int ammo2;
};
