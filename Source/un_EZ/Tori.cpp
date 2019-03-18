// Fill out your copyright notice in the Description page of Project Settings.

#include "Tori.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Engine/LocalPlayer.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "un_EZGameModeBase.h"

ATori::ATori()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->AirControl = 1.f;
	isMenuTori = false;
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
	if (isMenuTori)
		damageMultiplier = 0;

	/// Find better comment
	// Slow stuff
	if (slowDur.Num() > 0)
	{
		slowCheck(DeltaTime);
	}
	if (iTime > 0)
		iTime -= DeltaTime;

	if (dodgeAmmo < dodgeMaxAmmo)
	{
		dodgeCooldown -= DeltaTime;
		if (dodgeCooldown <= 0)
		{
			dodgeAmmo += 1;
			if (dodgeAmmo > dodgeMaxAmmo)
				dodgeAmmo = dodgeMaxAmmo;

			UE_LOG(LogTemp, Warning, TEXT("DodgeAmmo is %i now"), dodgeAmmo);

			dodgeCooldown = dodgeMaxCooldown;
		}
	}
	if (currentGlobalCooldown > 0)
	{
		currentGlobalCooldown -= DeltaTime;
		if (currentGlobalCooldown <= 0)
		{
			/// Add another visual indicator ingame
			UE_LOG(LogTemp, Warning, TEXT("GlobalCooldown finished"));
		}
	}

	// Make sure character position can't diviate from X = 0
	if (GetActorLocation().X != 0)
		SetActorLocation(FVector(0.f, GetActorLocation().Y, GetActorLocation().Z));

	checkIfLanded();
	if (GetVelocity().Z > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Going up!"));
		isGoingUp = true;
	}
	else
	{
		isGoingUp = false;
	}
}

void ATori::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move_X", this, &ATori::move_X);
	InputComponent->BindAxis("Move_Y", this, &ATori::move_Y);
	//InputComponent->BindAction("Dodge", IE_Pressed, this, &ATori::dodge);
	//InputComponent->BindAction("Dodge", IE_Released, this, &ATori::dodgeEnd);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ATori::Jump);

	InputComponent->BindAction("Ability_1", IE_Pressed, this, &ATori::ability_1);
	InputComponent->BindAction("Ability_1", IE_Released, this, &ATori::ability1End);

	InputComponent->BindAction("Ability_2", IE_Pressed, this, &ATori::ability_2);
	InputComponent->BindAction("Ability_2", IE_Released, this, &ATori::ability2End);

	InputComponent->BindAction("Switch_Element", IE_Pressed, this, &ATori::switchElement);
}

void ATori::move_X(float axisValue)
{
	//AddMovementInput(FVector(1, 0.f, 0.f), axisValue);
	if (!locked)
	{
		AddControllerPitchInput(axisValue);
	}
}

void ATori::move_Y(float axisValue)
{
	if (!locked)
	{
		AddMovementInput(FVector(0.f, 1, 0.f), axisValue);
		if (axisValue > 0)
			SetActorRotation(FRotator(0.f, 90.f, 0.f));
		if (axisValue < 0)
			SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void ATori::setMoveSpeed(float newMoveSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Setting movespeed to %f"), newMoveSpeed);
	GetCharacterMovement()->MaxWalkSpeed = newMoveSpeed;
}

void ATori::setRotationRate(float newRotationRate)
{
	//UE_LOG(LogTemp, Warning, TEXT("Setting rotation rate to %f"), newRotationRate);
	GetCharacterMovement()->RotationRate = FRotator(0.f, newRotationRate, 0.f);
}

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

void ATori::dodge()
{
	if(!isMenuTori)
		if (locked == false)
		{
			dodging = true;
			locked = true;
			iTime = 0.3f;
			FVector launchVector;
			launchVector = GetActorForwardVector() * dodgeRange;
			LaunchCharacter(launchVector, false, true);
			dodgeAmmo -= 1;
			if (element_1 != nullptr)
			{
				element_1->resetAbility1();
				element_1->resetAbility2();
			}
			if (element_2 != nullptr)
			{
				element_2->resetAbility1();
				element_2->resetAbility2();
			}
			setMoveSpeed(moveSpeed);
			setRotationRate(rotationRate);
		}
}
void ATori::dodgeEnd()
{
	if (!isMenuTori)
		dodging = false;
}

void ATori::jump()
{
	/// Make moving in air possible - Possible by getting current velocity, and manipulating this
	if (!locked && !isJumping)
	{
		this->LaunchCharacter(this->GetActorUpVector() * jumpForce, false, false);
		isJumping = true;
        }
}

void ATori::ability_1()
{
	if (locked == false)
	{
		if (currentGlobalCooldown <= 0)
		{
			if (activeElement == 1 && element_1 != nullptr)
			{
				element_1->ability1();
				element_1->channelingAbility1 = true;
			}
			else if (activeElement == 2 && element_2 != nullptr)
			{
				element_2->ability1();
				element_2->channelingAbility1 = true;
			}
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("GlobalCooldonw: %f"), currentGlobalCooldown);
	}
}

void ATori::ability1End()
{
	if (activeElement == 1 && element_1 != nullptr)
	{
		element_1->ability1End();
		element_1->channelingAbility1 = false;
	}
	else if (activeElement == 2 && element_2 != nullptr)
	{
		element_2->ability1End();
		element_2->channelingAbility1 = false;
	}
}

void ATori::ability_2()
{
	if (locked == false)
	{
		if (currentGlobalCooldown <= 0)
		{
			if (activeElement == 1 && element_1 != nullptr)
			{
				element_1->ability2();
				element_1->channelingAbility2 = true;
			}
			else if (activeElement == 2 && element_2 != nullptr)
			{
				element_2->ability2();
				element_2->channelingAbility2 = true;
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
	else if (activeElement == 2 && element_2 != nullptr)
	{
		element_2->ability2End();
		element_2->channelingAbility2 = false;
	}
}

void ATori::recieveDamage(float damage)
{
	// Might be something like this.
	if (iTime <= 0)
	{
		hitPoints -= damage * damageMultiplier;
		checkIfDead();
		if (!hitAnimImmune)
		{
			PlayAnimMontage(receiveDamageAnim, 1, FName("Start"));
			// So we dont lock characters forever.
			if (element_1 != nullptr)
			{
				element_1->resetAbility1();
				element_1->resetAbility2();
			}
			if (element_2 != nullptr)
			{
				element_2->resetAbility1();
				element_2->resetAbility2();
			}
			locked = 0;
		}
		freezeFrame(0.4, false);//Give this some good math for dmg becoming time frozen.
	}
	hitPointPercentage = hitPoints / maxHitPoints;
}

void ATori::recieveDamage(float damage, float ccDur, float slow, int type)
{
	// Type 0 is slow
	if (type == 0)
		if (iTime <= 0)
		{
			hitPoints -= damage * damageMultiplier;
			checkIfDead();
			wasHit = true;
			slowDur.Push(ccDur);
			slowAmount.Push(moveSpeed *((100 - slow)*0.01));
		}
	// Type 1 is stun
	if (type == 1)
	{
		hitPoints -= damage * damageMultiplier;
		/// Insert effect of stun
	}
	hitPointPercentage = hitPoints / maxHitPoints;
}
void ATori::recieveDamage(float damage, float knockback, FVector knockbackPoint)
{
	FVector delta = GetActorLocation() - knockbackPoint;
	delta.Normalize();
	FVector knockForce = delta * knockback;
	LaunchCharacter(knockForce, false, true);
	hitPoints -= damage * damageMultiplier;
	hitPointPercentage = hitPoints / maxHitPoints;
	checkIfDead();
	wasHit = true;
}

void ATori::checkIfDead()
{
	if (hitPoints <= 0)
	{
		DisableInput(Cast<APlayerController>(Controller));
		UE_LOG(LogTemp, Warning, TEXT("Player_ %i, is dead."), 1);
		if (!isDead)
			slowMoDeath(0.1f, 3.f);
		isDead = true;
		Cast<Aun_EZGameModeBase>(GetWorld()->GetAuthGameMode())->playerDead();
	}
}

bool ATori::pickUpElement(ABaseElement * newElement)
{
	// Checking for nullptrs are smart
	if (element_1 == nullptr)
	{
		element_1 = newElement;
		currentElementType = element_1->switchToElement(true);
	}
	else if (element_2 == nullptr && newElement->elementType != element_1->elementType)
	{
		element_2 = newElement;
	}
	// If it does not fill any empty spaces.
	else
	{
		if (newElement->elementType == element_1->elementType || newElement->elementType == element_2->elementType)
			return false;
		else
		{
			if (activeElement == 1)
			{
				element_1->Destroy();
				element_1 = newElement;
				//element_1->setPlayer(this);
				currentElementType = element_1->switchToElement(true);
				element_2->switchToElement(false);
			}
			else if (activeElement == 2)
			{
				element_2->Destroy();
				element_2 = newElement;
				//element_2->setPlayer(this);
				currentElementType = element_2->switchToElement(true);
				element_1->switchToElement(false);
			}
		}
	}
	switchAnimationElement();
	locked = false;
	setMoveSpeed(moveSpeed);
	setRotationRate(rotationRate);
	return true;
}

void ATori::switchElement()
{
	if (!isMenuTori)
		if (!locked)
		{
			if (activeElement == 1)
			{
				if (element_2 != nullptr)
				{
					activeElement = 2;
					currentElementType = element_2->switchToElement(true);
					element_1->switchToElement(false);
				}
			}
			else if (activeElement == 2)
			{
				if (element_1 != nullptr)
				{
					activeElement = 1;
					currentElementType = element_1->switchToElement(true);
					element_2->switchToElement(false);
				}
			}
			switchAnimationElement();
			locked = false;
			setMoveSpeed(moveSpeed);
			setRotationRate(rotationRate);
		}
}

void ATori::stopAllVelocity_Implementation()
{
	//no code here, just here to please the UE4 Gods!!!!
}

void ATori::clearElement()
{
	if(element_1 != nullptr)
		element_1->Destroy();
	element_1 = nullptr;
	if(element_2 != nullptr)
		element_2->Destroy();
	element_2 = nullptr;
}
