// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "WindElement.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility1.generated.h"

class AWindElement;


UCLASS()
class UN_EZ_API AWindElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	AWindElementAbility1();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	float attackRange;
	float chargedHit;
	float boltSpeed;
	float damage;
	float range;
	float distTraveled = 0.f;
	FVector spawnLocation;

	UPROPERTY(BlueprintReadWrite)
		class AWindElement* myElement;

	USphereComponent* collider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
