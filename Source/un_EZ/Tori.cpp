#include "Tori.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Engine/LocalPlayer.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "pickUp.h"
#include "un_EZGameModeBase.h"

ATori::ATori()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->AirControl = 1.f;
	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(GetMesh());
}

void ATori::BeginPlay()
{
	Super::BeginPlay();
	setMoveSpeed(moveSpeed);
	setRotationRate(rotationRate);
	maxSlow = moveSpeed;
	dodgeAmmo = dodgeMaxAmmo;
	dodgeCooldown = dodgeMaxCooldown;
	hitPoints = maxHitPoints;
	hitPointPercentage = hitPoints / maxHitPoints;
	locked = false;
}

void ATori::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (slowDur.Num() > 0)
	{
		slowCheck(DeltaTime);
	}
	if (iTime > 0)
		iTime -= DeltaTime;

	if (currentGlobalCooldown > 0)
	{
		currentGlobalCooldown -= DeltaTime;
	}

	// Make sure character position can't diviate from X = 0
	if (GetActorLocation().X != 0)
		SetActorLocation(FVector(0.f, GetActorLocation().Y, GetActorLocation().Z));

	checkIfLanded();
	if (GetVelocity().Z > 0)
	{
		isGoingDown = false;
		isGoingUp = true;
	}
	else
	{
		isGoingDown = false;
		isGoingUp = false;
	}

	if (forceTime > 0.f + DeltaTime)
	{
		FVector tempLocation = GetActorLocation();
		tempLocation += (forceMoveDirection * forceSpeed * DeltaTime);
		SetActorLocation(tempLocation);
		forceTime -= DeltaTime;
	}
}

void ATori::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move_Y", this, &ATori::move_Y);
	InputComponent->BindAxis("Move_X", this, &ATori::move_X);
	InputComponent->BindAction("XButtonDown", IE_Pressed, this, &ATori::XButtonDown);
	InputComponent->BindAction("XButtonDown", IE_Released, this, &ATori::XButtonDownEnd);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ATori::jump);
	InputComponent->BindAction("Ability_1", IE_Pressed, this, &ATori::ability_1);
	InputComponent->BindAction("Ability_1", IE_Released, this, &ATori::ability1End);
	InputComponent->BindAction("Ability_2", IE_Pressed, this, &ATori::ability_2);
	InputComponent->BindAction("Ability_2", IE_Released, this, &ATori::ability2End);
	InputComponent->BindAction("Switch_Element", IE_Pressed, this, &ATori::switchElement);
}

void ATori::move_X(float axisValue)
{
	facingDirection.Z = axisValue;
	if (axisValue < -moveXDeadZone && onSolidGround == false)
	{
		stopCollision();
		isGoingDown = true;
		if (GetVelocity().Z <= 0.f)
			LaunchCharacter(GetActorUpVector() * -1, false, false);
	}
}

void ATori::XButtonDown()
{
	// This is used for WindAbility1 
}

void ATori::move_Y(float axisValue)
{
	facingDirection.Y = axisValue;
	if (!moveLocked)
	{
		AddMovementInput(FVector(0.f, 1, 0.f), axisValue);
		if (axisValue > 0)
			desiredRotation = FRotator(0.f, 90.f, 0.f);
		if (axisValue < 0)
			desiredRotation = FRotator(0.f, -90.f, 0.f);
	}
	if (snapRotation)
	{
		if (axisValue > 0)
			SetActorRotation(FRotator(0.f, 90.f, 0.f));
		if (axisValue < 0)
			SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void ATori::setMoveSpeed(float newMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = newMoveSpeed;
}

void ATori::setRotationRate(float newRotationRate)
{
	GetCharacterMovement()->RotationRate = FRotator(0.f, newRotationRate, 0.f);
}

// Avoids having multiple stacks of slow (This also ensures only the strongest slow is active)
// Adds the weaker slow, if its duration is still above 0, when a stronger slow ends
void ATori::slowCheck(float DeltaTime)
{
	for (int i = 0; i < slowDur.Num(); i++)
	{
		slowDur[i] -= DeltaTime;
		if (slowAmount[i] < maxSlow)
		{
			maxSlow = slowAmount[i];
		}
		if (currentSpeed > maxSlow)
		{
			setMoveSpeed(maxSlow);
		}
		if (slowDur[i] <= 0)
		{
			slowDur.RemoveAt(i);
			slowAmount.RemoveAt(i);
			if (slowDur.Num() == 0)
			{
				setMoveSpeed(moveSpeed);
				maxSlow = moveSpeed;
			}
		}
	}
}

void ATori::jump()
{
	if (!GetCharacterMovement()->IsFalling())
		Jump();
	else
	{
		if (JumpCurrentCount == 0)
		{
			if ((JumpCurrentCount + 1) < JumpMaxCount)
			{
				GetMovementComponent()->Velocity = facingDirection.GetSafeNormal() * GetCharacterMovement()->JumpZVelocity * 0.8f;
				dashAnim();
			}
			JumpCurrentCount += 2;
		}
		else if (JumpCurrentCount < JumpMaxCount)
		{
			GetMovementComponent()->Velocity = facingDirection.GetSafeNormal() * GetCharacterMovement()->JumpZVelocity * 0.8f;
			JumpCurrentCount++;
			dashAnim();
		}
	}
}

// Used for some abilities that moves the user in a direction
void ATori::forceMove(FVector direction, float speed, float time)
{
	forceMoveDirection = direction;
	forceSpeed = speed;
	forceTime = time;
}

void ATori::ability_1()
{
	if (locked == false)
	{
		SetActorRotation(desiredRotation);
		if (currentGlobalCooldown <= 0)
		{
			if (activeElement == 1 && element_1 != nullptr)
			{
				element_1->ability1();
				element_1->channelingAbility1 = true;
			}
		}
	}
}

void ATori::ability1End()
{
	if (activeElement == 1 && element_1 != nullptr)
	{
		element_1->ability1End();
		element_1->channelingAbility1 = false;
	}
}

void ATori::ability_2()
{
	if (locked == false)
	{
		SetActorRotation(desiredRotation);
		if (currentGlobalCooldown <= 0)
		{
			if (activeElement == 1 && element_1 != nullptr)
			{
				element_1->ability2();
				element_1->channelingAbility2 = true;
			}
		}
	}
}

void ATori::ability2End()
{
	if (activeElement == 1 && element_1 != nullptr)
	{
		element_1->ability2End();
		element_1->channelingAbility2 = false;
	}
}

// Standard recieveDamage function
void ATori::recieveDamage(ATori* attacker, float damage)
{
	lastAttacker = attacker;
	if (iTime <= 0)
	{
		hitPoints -= damage * damageMultiplier;
		checkIfDead();
		if (!hitAnimImmune)
		{
			FVector delta = GetActorLocation() - attacker->GetActorLocation();
			delta.Normalize();
			takeHitAnim(delta);
			// So we dont lock characters forever.
			if (element_1 != nullptr)
			{
				element_1->resetAbility1();
				element_1->resetAbility2();
			}
			locked = 0;
		}
		freezeFrame(0.4, false);//Give this some good math for dmg becoming time frozen.
	}
	hitPointPercentage = hitPoints / maxHitPoints;
}

// recieveDamage with slow effect
void ATori::recieveDamage(ATori* attacker, float damage, float ccDur, float slow, int type)
{
	lastAttacker = attacker;
	// Type 0 is slow
	if (type == 0)
		if (iTime <= 0)
		{
			hitPoints -= damage * damageMultiplier;
			checkIfDead();
			wasHit = true;
			slowDur.Push(ccDur);
			slowAmount.Push(moveSpeed *((100 - slow)*0.01));
			if (!hitAnimImmune)
			{
				FVector delta = GetActorLocation() - attacker->GetActorLocation();
				delta.Normalize();
				takeHitAnim(delta);
				// So we dont lock characters forever.
				if (element_1 != nullptr)
				{
					element_1->resetAbility1();
					element_1->resetAbility2();
				}
				locked = 0;
			}
			freezeFrame(0.4, false);//Give this some good math for dmg becoming time frozen.
		}
	// Type 1 is stun (No ability ingame uses stun as of now)
	if (type == 1)
	{
		hitPoints -= damage * damageMultiplier;
	}
	hitPointPercentage = hitPoints / maxHitPoints;
}

// recieveDamage with knockback effect
void ATori::recieveDamage(ATori* attacker, float damage, float knockback, FVector knockbackPoint)
{
	lastAttacker = attacker;
	FVector delta = GetActorLocation() - knockbackPoint;
	delta.Normalize();
	FVector knockForce = delta * knockback;
	knockForce.Z = 0.f;
	LaunchCharacter(knockForce, false, true);
	hitPoints -= damage * damageMultiplier;
	hitPointPercentage = hitPoints / maxHitPoints;
	checkIfDead();
	wasHit = true;
	if (!hitAnimImmune)
	{
		FVector delta = GetActorLocation() - attacker->GetActorLocation();
		delta.Normalize();
		takeHitAnim(delta);
		// So we dont lock characters forever.
		if (element_1 != nullptr)
		{
			element_1->resetAbility1();
			element_1->resetAbility2();
		}
		locked = 0;
	}
	freezeFrame(0.4, false);//Give this some good math for dmg becoming time frozen.
}

void ATori::checkIfDead()
{
	if (hitPoints <= 0)
	{
		lastAttacker->gainPoint();
		DisableInput(Cast<APlayerController>(Controller));
		UE_LOG(LogTemp, Warning, TEXT("Player_ %i, is dead."), PlayerNumber);
		if (!isDead)
			slowMoDeath(0.1f, 3.f);
		isDead = true;
		Cast<Aun_EZGameModeBase>(GetWorld()->GetAuthGameMode())->playerDead();
	}
}

bool ATori::pickUpElement(ABaseElement * newElement)
{
	if (element_1 == nullptr)
	{
		element_1 = newElement;
		currentElementType = element_1->switchToElement(true);
	}

	// If it does not fill any empty spaces.
	else
	{
		if (newElement->elementType == element_1->elementType)
			return false;
		else
		{
			if (activeElement == 1)
			{
				element_1->Destroy();
				element_1 = newElement;
				currentElementType = element_1->switchToElement(true);
			}
		}
	}
	switchAnimationElement();
	locked = false;
	setMoveSpeed(moveSpeed);
	setRotationRate(rotationRate);
	return true;
}

// Used to pick up a new element
void ATori::switchElement()
{
	if (!locked)
		if (currentPickUp != nullptr)
		{
			currentPickUp->giveElement(this);
		}
}

void ATori::stopAllVelocity_Implementation()
{
	// No code here, just here to please the UE4 Gods!!!!
}
