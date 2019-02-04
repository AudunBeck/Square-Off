// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "WaterElement.h"
#include "Tori.h"
#include "GameFramework/Actor.h"
#include "WaterElementAbility1.generated.h"

class AWaterElement;

UCLASS()
class UN_EZ_API AWaterElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterElementAbility1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// slow is set in %, where 25.5 = 25.5% slow
	float attackRange;
	float chargedHit;
	float boltSpeed;
	float ccDur;
	float slow;
	float damage;

	USphereComponent* collider;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		class AWaterElement* myElement;
	// Add a description here
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
