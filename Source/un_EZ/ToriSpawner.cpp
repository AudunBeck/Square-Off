#include "ToriSpawner.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"

AToriSpawner::AToriSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->AirControl = 1.f;
}

void AToriSpawner::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->GravityScale = 0.f;
}

// Called every frame
void AToriSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (inAxis == 0)
		GetCharacterMovement()->StopMovementImmediately();
}

// Called to bind functionality to input
void AToriSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Move_Y", this, &AToriSpawner::moveDirection);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AToriSpawner::spawnPlayer);
	InputComponent->BindAction("Ability_1", IE_Pressed, this, &AToriSpawner::spawnPlayer);
	InputComponent->BindAction("Ability_2", IE_Pressed, this, &AToriSpawner::spawnPlayer);
	InputComponent->BindAction("Switch_Element", IE_Pressed, this, &AToriSpawner::spawnPlayer);
}

void AToriSpawner::moveDirection(float AxisValue)
{
	AddMovementInput(FVector(0.f, 1, 0.f), AxisValue);
	inAxis = AxisValue;
}
