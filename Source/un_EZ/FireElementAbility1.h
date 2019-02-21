// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "FireElement.h"
#include "Tori.h"
#include "FireElementAbility1.generated.h"

UCLASS()
class UN_EZ_API AFireElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	AFireElementAbility1();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	class AFireElement* myElement;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		USphereComponent* collider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
		void beginSound();

	UPROPERTY(BlueprintReadWrite)
		bool buffed = false;
	float attackRange = 100;
	float damage;

};
