// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "Tori.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "FireElementAbility2.generated.h"

UCLASS()
class UN_EZ_API AFireElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireElementAbility2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Owner of the attack
	void setupAttack(ATori * newOwner, float lifeSpan, float range);

	UPROPERTY(EditAnywhere, Category = "Ability2")
		class ATori* myOwner;

	float attackRange;
};
