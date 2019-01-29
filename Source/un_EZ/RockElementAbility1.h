// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "RockElement.h"
#include "Tori.h"
#include "RockElementAbility1.generated.h"

UCLASS()
class UN_EZ_API ARockElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockElementAbility1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Owner of the attack
	float attackRange;
	float chargedHit;
	UPROPERTY(EditAnywhere)
		class ARockElement* myElement;
	USphereComponent* collider;
	
	
	
	FVector ownerPos;

	// Add a description here
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
