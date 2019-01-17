// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/Classes/Components/ChildActorComponent.h"
#include "BaseElement.h"
#include "Tori.generated.h"

UCLASS()
class UN_EZ_API ATori : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATori();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void move_X(float axisValue);
	void move_Y(float axisValue);

	void ability_1();
	void ability_2();

	// Made for the pickup to access this and send new element to the player, is a bool to check if it already contains it and will not destroy the pickup.
	bool pickUpElement(class ABaseElement* newElement);

	UPROPERTY(EditAnywhere, Category = "Elements")
		int activeElement = 1;
	void switchElement();

	UPROPERTY(EditAnywhere, Category = "Elements")
		class ABaseElement* element_1;
	UPROPERTY(EditAnywhere, Category = "Elements")
		class ABaseElement* element_2;

};
