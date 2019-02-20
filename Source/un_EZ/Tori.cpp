// Fill out your copyright notice in the Description page of Project Settings.

#include "Tori.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Engine/LocalPlayer.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/GameEngine.h"
#include "un_EZGameModeBase.h"

// Sets default values
ATori::ATori()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
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
}

// Called every frame
void ATori::Tick(float DeltaTime)
{
	/// Find better comment
	// Slow stuff
	if (slowDur.Num() > 0)
	{
		slowCheck(DeltaTime);
	}

	if (locked > 0)
		locked -= DeltaTime;
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
}

// Called to bind functionality to input
void ATori::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move_X", this, &ATori::move_X);
	InputComponent->BindAxis("Move_Y", this, &ATori::move_Y);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &ATori::dodge);
	InputComponent->BindAction("Dodge", IE_Released, this, &ATori::dodgeEnd);

	InputComponent->BindAction("Ability_1", IE_Pressed, this, &ATori::ability_1);
	InputComponent->BindAction("Ability_1", IE_Released, this, &ATori::ability1End);

	InputComponent->BindAction("Ability_2", IE_Pressed, this, &ATori::ability_2);
	InputComponent->BindAction("Ability_2", IE_Released, this, &ATori::ability2End);

	InputComponent->BindAction("Switch_Element", IE_Pressed, this, &ATori::switchElement);

}

void ATori::addForce(FVector pushDirection)
{
	myPushVector = pushDirection;
}

void ATori::move_X(float axisValue)
{
	AddMovementInput(FVector(1, 0.f, 0.f), axisValue);
}

void ATori::move_Y(float axisValue)
{
	AddMovementInput(FVector(0.f, 1, 0.f), axisValue);
}

void ATori::setMoveSpeed(float newMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = newMoveSpeed;
	//UE_LOG(LogTemp, Warning, TEXT("Speed is now %f"), newMoveSpeed);
}

void ATori::setRotationRate(float newRotationRate)
{
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
			//UE_LOG(LogTemp, Warning, TEXT("Removing slow num: %i"), i);
			if (slowDur.Num() == 0)
			{
				setMoveSpeed(moveSpeed);
				maxSlow = moveSpeed;
				//UE_LOG(LogTemp, Warning, TEXT("Normal speed"));
			}
		}
	}
}

void ATori::dodge()
{
	if (locked <= 0)
	{
		if (dodgeAmmo > 0)
		{
			dodging = true;
			locked = 0.5f;
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
	
		}
	}
}
void ATori::dodgeEnd()
{
	dodging = false;
}

void ATori::ability_1()
{
	if (locked <= 0)
	{
		if (currentGlobalCooldown <= 0)
		{
			if (activeElement == 1 && element_1 != nullptr)
				element_1->ability1();
			else if (activeElement == 2 && element_2 != nullptr)
				element_2->ability1();
			currentGlobalCooldown = globalCooldown;
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("GlobalCooldonw: %f"), currentGlobalCooldown);
	}
}

void ATori::ability1End()
{

	//if (activeElement == 1 && element_1 != nullptr)
	//	element_1->ability1End();
	//else if (activeElement == 2 && element_2 != nullptr)
	//	element_2->ability1End();

}

void ATori::ability_2()
{
	if (locked <= 0)
	{
		if (currentGlobalCooldown <= 0)
		{
			if (activeElement == 1 && element_1 != nullptr)
				element_1->ability2();
			else if (activeElement == 2 && element_2 != nullptr)
				element_2->ability2();
			currentGlobalCooldown = globalCooldown;
			

		}
	}
}

void ATori::ability2End()
{

	//if (activeElement == 1 && element_1 != nullptr)
	//	element_1->ability2End();
	//else if (activeElement == 2 && element_2 != nullptr)
	//	element_2->ability2End();

}

void ATori::recieveDamage(float damage)
{
	// Might be something like this.
	//int playerNum = Cast<APlayerController>(GetController())->GetLocalPlayer()->GetControllerId();
	if (iTime <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has %f hitpoints left"), hitPoints); // Find a way to find the player-number, instead of 1
		UE_LOG(LogTemp, Warning, TEXT("Damage multiplier: %f"), damageMultiplier);
		hitPoints -= damage * damageMultiplier;
		checkIfDead();
		wasHit = true;
	}
	hitPointPercentage = hitPoints / maxHitPoints;
}

void ATori::recieveDamage(float damage, float ccDur, float slow, int type)
{
	// Type 0 is slow
	if (type == 0)
		if (iTime <= 0)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Player_ %i, was struck."), 1); // Find a way to find the player-number, instead of 1
			hitPoints -= damage * damageMultiplier;
			checkIfDead();
			wasHit = true;

			slowDur.Push(ccDur);
			slowAmount.Push(moveSpeed *((100 - slow)*0.01));
			UE_LOG(LogTemp, Warning, TEXT("There are now %i slows"), slowDur.Num());
		}

	// Type 1 is stun
	if (type == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player_ %i, was struck."), 1); // Find a way to find the player-number, instead of 1
		hitPoints -= damage * damageMultiplier;
		
		/// Incert effect of stun
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
		currentElementType = element_1->switchToElement();

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
				currentElementType = element_1->switchToElement();

			}
			else if (activeElement == 2)
			{
				element_2->Destroy();
				element_2 = newElement;
				//element_2->setPlayer(this);
				currentElementType = element_2->switchToElement();

			}
		}
	}

	switchAnimationElement();
	return true;
}

void ATori::switchElement()
{
	if (locked <= 0)
	{
		if (activeElement == 1)
		{
			activeElement = 2;
			if (element_2 != nullptr)
				currentElementType = element_2->switchToElement();
		}
		else if (activeElement == 2)
		{
			activeElement = 1;
			if (element_1 != nullptr)
				currentElementType = element_1->switchToElement();
		}
		switchAnimationElement();
		
		
		UE_LOG(LogTemp, Warning, TEXT("Active element is now %i"), activeElement);
	}
}

void ATori::stopAllVelocity_Implementation()
{
	//no code here, just here to please the UE4 Gods!!!!
}

