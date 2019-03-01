// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "BaseElement.h"
#include "pickUp.generated.h"

class ApickUpSpawner;
UCLASS()
class UN_EZ_API ApickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	ApickUp();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
		USphereComponent* collider;

	UPROPERTY(EditAnywhere, Category = "Element")
		TSubclassOf<class ABaseElement> ElementBlueprint;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void StartDestroy();

	ApickUpSpawner* mySpawner;
};
