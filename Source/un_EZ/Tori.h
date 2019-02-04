// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	void addForce(FVector pushDirection);

	// Runs movement for the character.
	void move_X(float axisValue);
	void move_Y(float axisValue);

	void setMoveSpeed(float newMoveSpeed);
	void setRotationRate(float newRotationSpeed);
	float currentSpeed;
	float maxSlow;
	void slowCheck(float DeltaTime);
	void dodge();

	FVector myPushVector;

	// Runs abilities, sends to the element it has equipped currently.
	void ability_1();
	void ability1End();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability1Used = false;

	void ability_2();
	void ability2End();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability2Used = false;


	UPROPERTY(EditAnywhere, Category = "HitPoints")
		float maxHitPoints = 100;
	float hitPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitPoints")
		float hitPointPercentage;
	

	TArray<float> slowDur;
	TArray<float> slowAmount;

	// Recieve damage
	float damageMultiplier = 1.f;
	void recieveDamage(float damage);
	void recieveDamage(float damage, float slow, float ccDur, int type);		//Int type defines effect, 0 = slow, 1 = stun
	void recieveDamage(float damage, float knockback, FVector knockbackPoint);
	

	// Made for the pickup to access this and send new element to the player, is a bool to check if it already contains it and will not destroy the pickup.
	bool pickUpElement(class ABaseElement* newElement);

	// For switching between the 2 elements you have currently.
	UPROPERTY(EditAnywhere, Category = "Elements")
		int activeElement = 1;


	void switchElement();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void switchAnimationElement();
	UPROPERTY (VisibleAnywhere, BluePrintReadOnly, Category = "Animations")
	int currentElementType = 0;
	

	// Holds the pointers for the elements you currently have.
	UPROPERTY(EditAnywhere, Category = "Elements")
		class ABaseElement* element_1;
	UPROPERTY(EditAnywhere, Category = "Elements")
		class ABaseElement* element_2;
	UPROPERTY(EditAnywhere, Category = "Elements")
		float globalCooldown;
	float currentGlobalCooldown;


	UPROPERTY(EditAnywhere, Category = "Movement")
		float locked; // How long the control of the character is locked.
	UPROPERTY(EditAnywhere, Category = "Movement")
		float moveSpeed = 600;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float rotationRate = 720;
	UPROPERTY(EditAnywhere, Category = "Movement")
		int dodgeMaxAmmo = 2;
	UPROPERTY(EditAnywhere, Category = "Movement")
		int dodgeAmmo;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float dodgeMaxCooldown = 10;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float dodgeCooldown;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float dodgeRange;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float iTime; // How long the character is invunrable to damage.


};
