#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseElement.h"
#include "Tori.generated.h"

class ApickUp;
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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void move_Y(float axisValue);
	void move_X(float axisValue);
	void XButtonDown();
	float currentSpeed;
	float maxSlow;
	void slowCheck(float DeltaTime);
	void jump();

	// ForceMove
	void forceMove(FVector direction = FVector{ 0.f, 0.f, 0.f }, float speed = 0.f, float time = 0.f);
	FVector forceMoveDirection;
	float forceSpeed;
	float forceTime;
	FVector myPushVector;

	// Check if stuck
	float currentZ;
	float tempZ;

	// Runs ability 1
	void ability_1();
	void ability1End();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability1Used = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability1Ended = false;

	// Runs ability 2
	void ability_2();
	void ability2End();
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability2Used = false;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Animations")
		bool ability2Ended = false;


	// Health values
	UPROPERTY(EditAnywhere, Category = "HitPoints")
		float maxHitPoints = 100;

	float hitPoints;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitPoints")
		float hitPointPercentage;

	// Slow values
	TArray<float> slowDur;
	TArray<float> slowAmount;

	// Recieve damage
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
		float damageMultiplier = 1.f;
	void recieveDamage(ATori* attacker, float damage);
	void recieveDamage(ATori* attacker, float damage, float slow, float ccDur, int type);		//Int type defines effect, 0 = slow, 1 = stun
	void recieveDamage(ATori* attacker, float damage, float knockback, FVector knockbackPoint);
	UPROPERTY(EditAnywhere, Category = "Animations")
		UAnimMontage * receiveDamageAnim;
	void checkIfDead();
	UPROPERTY(BlueprintReadWrite, Category = "Damage")
		ATori* lastAttacker;


	// Element values, and swapping
	void switchElement();
	bool pickUpElement(class ABaseElement* newElement);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elements")
		int activeElement = 1;

	// Cooldown values
	float currentGlobalCooldown;
	UPROPERTY(EditAnywhere, Category = "Elements")
		float globalCooldown;

	// Various variables for blueprints
	// Player info
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int PlayerNumber;

	// Movement variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float moveXDeadZone = 0.5f;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool onSolidGround = false;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
		void stopCollision();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Movement")
		bool snapRotation = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		bool locked; // How long the control of the character is locked.

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
		bool moveLocked; // How long the control of the character is locked.

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float moveSpeed = 600;

	FRotator desiredRotation;
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement")
		void stopAllVelocity();

	// Animation variables
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animations")
		bool stillFiring1 = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Animations")
		bool finishedCombo1 = false;

	UPROPERTY(BlueprintReadWrite, Category = "Animations")
		bool hitAnimImmune = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animations")
		bool dodging;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animations")
		bool wasHit;

	// Misc variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Arms = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector facingDirection;


	// Various functions for blueprints
	// Movement functions
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
		void gainPoint();

	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
		void XButtonDownEnd();

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void setMoveSpeed(float newMoveSpeed);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void setRotationRate(float newRotationSpeed);

	// Animation functions
	UFUNCTION(BlueprintImplementableEvent, Category = "Animations")
		void dashAnim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void switchAnimationElement();

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Animations")
		int currentElementType = 0;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Animations")
		bool isDead = false;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void freezeFrame(float timeFrozen, bool endAnim = false);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Animations")
		void takeHitAnim(FVector direction);

	// Element functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elements")
		class ABaseElement* element_1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elements")
		class ApickUp* currentPickUp;

	// Misc functions
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void slowMoDeath(float slowMoEffect, float slowMoTime);
};
