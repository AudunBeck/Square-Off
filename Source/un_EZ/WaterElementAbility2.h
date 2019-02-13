// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "WaterElement.h"
#include "GameFramework/Actor.h"
#include "WaterElementAbility2.generated.h"

class AWaterElement;

UCLASS()
class UN_EZ_API AWaterElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterElementAbility2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float currBuffDur;
	float dashDist;
	float ccDur;
	float slow;
	float damage;

	UPROPERTY(EditAnywhere, Category = "Ability2", BlueprintReadOnly)
		class AWaterElement* myElement;

	USphereComponent* collider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
