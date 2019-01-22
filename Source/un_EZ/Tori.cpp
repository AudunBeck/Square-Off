// Fill out your copyright notice in the Description page of Project Settings.

#include "Tori.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Engine/LocalPlayer.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Engine/GameEngine.h"

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
	
}

// Called every frame
void ATori::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Controllers's Rotation is %s"),
	//	*GetControlRotation().ToString());

	//UE_LOG(LogTemp, Warning, TEXT("MyCharacter's ForwardVector is %s"),
	//	*GetActorForwardVector().ToString());


}

// Called to bind functionality to input
void ATori::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move_X", this, &ATori::move_X);
	InputComponent->BindAxis("Move_Y", this, &ATori::move_Y);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &ATori::dodge);

	InputComponent->BindAction("Ability_1", IE_Pressed, this, &ATori::ability_1);
	InputComponent->BindAction("Ability_1", IE_Released, this, &ATori::ability1End);

	InputComponent->BindAction("Ability_2", IE_Pressed, this, &ATori::ability_2);
	InputComponent->BindAction("Ability_2", IE_Released, this, &ATori::ability2End);

	InputComponent->BindAction("Switch_Element", IE_Pressed, this, &ATori::switchElement);



}

void ATori::move_X(float axisValue)
{
	AddMovementInput(FVector(1, 0.f, 0.f), axisValue);
}

void ATori::move_Y(float axisValue)
{
	AddMovementInput(FVector(0.f, 1, 0.f), axisValue);
}

void ATori::setMoveSpeed (float newMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = newMoveSpeed;
}

void ATori::setRotationRate(float newRotationRate)
{
	GetCharacterMovement()->RotationRate = FRotator(0.f, newRotationRate, 0.f);
}

void ATori::dodge()
{
}

void ATori::ability_1()
{
	if (activeElement == 1 && element_1 != nullptr)
		element_1->ability1();
	else if (activeElement == 2 && element_2 != nullptr)
		element_2->ability1();
}

void ATori::ability1End()
{
	if (activeElement == 1 && element_1 != nullptr)
		element_1->ability1End();
	else if (activeElement == 2 && element_2 != nullptr)
		element_2->ability1End();
}

void ATori::ability_2()
{
	if (activeElement == 1 && element_1 != nullptr)
		element_1->ability2();
	else if (activeElement == 2 && element_2 != nullptr)
		element_2->ability2();
}

void ATori::ability2End()
{
	if (activeElement == 1 && element_1 != nullptr)
		element_1->ability2End();
	else if (activeElement == 2 && element_2 != nullptr)
		element_2->ability2End();
}

void ATori::recieveDamage(float damage)
{
	// Might be something like this.
	//int playerNum = Cast<APlayerController>(GetController())->GetLocalPlayer()->GetControllerId();

	UE_LOG(LogTemp, Warning, TEXT("Player_ %i, was struck."), 1); // Find a way to find the player-number, instead of 1
	hitPoints -= damage;
	if (hitPoints <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player_ %i, is dead."), 1);
	}
}

bool ATori::pickUpElement(ABaseElement * newElement)
{
	// Checking for nullptrs are smart
	if (element_1 == nullptr)
		element_1 = newElement;
	else if (element_2 == nullptr && newElement->elementType != element_1->elementType)
		element_2 = newElement;
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
				element_1->setPlayer(this);
			}
			else if (activeElement == 2)
			{
				element_2->Destroy();
				element_2 = newElement;
				element_2->setPlayer(this);
			}
		}
	}
	return true;
}

void ATori::switchElement()
{
	if (activeElement == 1)
		activeElement = 2;
	else if (activeElement == 2)
		activeElement = 1;
	UE_LOG(LogTemp, Warning, TEXT("Active element is now %i"), activeElement);
}

