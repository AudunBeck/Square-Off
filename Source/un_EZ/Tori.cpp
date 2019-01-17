// Fill out your copyright notice in the Description page of Project Settings.

#include "Tori.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
}

// Called every frame
void ATori::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Controllers's Rotation is %s"),
		*GetControlRotation().ToString());

	UE_LOG(LogTemp, Warning, TEXT("MyCharacter's ForwardVector is %s"),
		*GetActorForwardVector().ToString());

}

// Called to bind functionality to input
void ATori::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move_X", this, &ATori::move_X);
	InputComponent->BindAxis("Move_Y", this, &ATori::move_Y);


}

void ATori::move_X(float axisValue)
{
	/*
	if ((GetController() != NULL) && (axisValue != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0); 
		//found this easier than other methods since it just adds a float value, and can be changed into any direction.

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, axisValue);
		
	}	
	*/
	AddMovementInput(FVector(1, 0.f, 0.f), axisValue);
}

void ATori::move_Y(float axisValue)
{
	/*
	if ((GetController() != NULL) && (axisValue != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, axisValue);
		
	}
	*/
	AddMovementInput(FVector(0.f, 1, 0.f), axisValue);
}

