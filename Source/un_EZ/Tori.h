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
	ATori();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Runs movement for the character.
	void move_Y(float axisValue);
	void move_X();

	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
		void move_XEnd();
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void setMoveSpeed(float newMoveSpeed);
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void setRotationRate(float newRotationSpeed);
	float currentSpeed;
	float maxSlow;
	void slowCheck(float DeltaTime);
	void dodge();
	void dodgeEnd();
	void jump();

	//UPROPERTY(EditAnywhere)
	//	UMovementComponent* PhysicsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float inAirMoceForce = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float jumpForce = 800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isJumping = false;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
		void checkIfLanded();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isGoingUp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isGoingDown = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animations")
		bool dodging;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animations")
		bool wasHit;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool isMenuTori;

	FVector myPushVector;

	// Runs abilities, sends to the element it has equipped currently.
	void ability_1();
	void ability1End();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability1Used = false;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability1Ended = false;


	void ability_2();
	void ability2End();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability2Used = false;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability2Ended = false;

	// Health properties
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
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage * receiveDamageAnim;

	void checkIfDead();


	// Made for the pickup to access this and send new element to the player, is a bool to check if it already contains it and will not destroy the pickup.
	bool pickUpElement(class ABaseElement* newElement);

	// For switching between the 2 elements you have currently.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elements")
		int activeElement = 1;

	void switchElement();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void switchAnimationElement();
	UPROPERTY (VisibleAnywhere, BluePrintReadOnly, Category = "Animations")
		int currentElementType = 0;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Animations")
		bool isDead = false;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void freezeFrame(float timeFrozen, bool endAnim = false);

	// Holds the pointers for the elements you currently have.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elements")
		class ABaseElement* element_1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elements")
		class ABaseElement* element_2;
	UPROPERTY(EditAnywhere, Category = "Elements")
		float globalCooldown;
	float currentGlobalCooldown;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement")
		void stopAllVelocity();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		bool locked; // How long the control of the character is locked.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float moveSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
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
	FRotator desiredRotation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animations")
		bool stillFiring1 = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animations")
		bool finishedCombo1 = false;
	bool hitAnimImmune = false;
	UFUNCTION(BlueprintCallable, Category = "MenuTori")
		void clearElement();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void slowMoDeath(float slowMoEffect, float slowMoTime);
	


};
