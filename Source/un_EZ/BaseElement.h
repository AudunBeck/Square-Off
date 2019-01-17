// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	bool isActive;

	// Ability 1 variables.
	void ability1();

	UPROPERTY(EditAnywhere)
		float maxCooldownAbility1;
	UPROPERTY(EditAnywhere)
		float cooldownAbility1;
	UPROPERTY(EditAnywhere)
		int maxAmmo1;
	UPROPERTY(EditAnywhere)
		int ammo1;



	// Ability 2 variables.
	void ability2();

	UPROPERTY(EditAnywhere)
		float maxCooldownAbility2;
	UPROPERTY(EditAnywhere)
		float cooldownAbility2;
	UPROPERTY(EditAnywhere)
		int maxAmmo2;
	UPROPERTY(EditAnywhere)
		int ammo2;

	






};
