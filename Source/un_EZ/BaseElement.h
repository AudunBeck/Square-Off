// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tori.h"
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

	int elementType = 0;

	bool isActive;

	// Setting Owner
	void setOwner(class ATori* newOwner);

	UPROPERTY(EditAnywhere)
		class ATori* myOwner;

	// Ability 1 variables.
	virtual void ability1();

	UPROPERTY(EditAnywhere)
		float maxCooldownAbility1;
	UPROPERTY(EditAnywhere)
		float cooldownAbility1;
	UPROPERTY(EditAnywhere)
		int maxAmmo1;
	UPROPERTY(EditAnywhere)
		int ammo1;



	// Ability 2 variables.
	virtual void ability2();

	UPROPERTY(EditAnywhere)
		float maxCooldownAbility2;
	UPROPERTY(EditAnywhere)
		float cooldownAbility2;
	UPROPERTY(EditAnywhere)
		int maxAmmo2;
	UPROPERTY(EditAnywhere)
		int ammo2;

	






};
