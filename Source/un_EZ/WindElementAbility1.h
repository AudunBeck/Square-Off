// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Tori.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility1.generated.h"

/**
 * 
 */
UCLASS()
class UN_EZ_API AWindElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWindElementAbility1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setupAttack(ATori* newOwner, float lifeSpan, float boltSpeedIn, float damageIn);
	float attackRange;
	float chargedHit;
	float boltSpeed;
	float damage;

	USphereComponent* collider;

	// Add a description here
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};