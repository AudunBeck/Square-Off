#include "WaterElement.h"
#include "ConstructorHelpers.h"
#include "WaterElementStruct.h"

AWaterElement::AWaterElement()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable>
		WaterElementTable(TEXT("DataTable'/Game/DataTables/WaterElementTable.WaterElementTable'"));
	BalancingTable = WaterElementTable.Object;

	//Searching and getting data
	FWaterElementStruct* Ability1Data = BalancingTable->FindRow<FWaterElementStruct>(FName("1"), FString(""));
	FWaterElementStruct* Ability2Data = BalancingTable->FindRow<FWaterElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		damage = Ability1Data->Damage;
		ability1Range = Ability1Data->Range;
		boltSpeed = Ability1Data->MoveRange;
		ability1lifeSpan = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		dashSpeed_2 = Ability2Data->MoveRange;
		ability2Knockback = Ability2Data->Knockback;
		ability2lifeSpan = Ability2Data->LifeSpan;
	}
}

void AWaterElement::BeginPlay()
{
	Super::BeginPlay();
}

void AWaterElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Ability 2
	if (buffDur >= 0)
	{
		myOwner->setMoveSpeed(0.f);	/// Movementspeed isn't affected - Look into
		buffDur -= DeltaTime;
		if (buffDur <= 0)
		{
			myOwner->setMoveSpeed(myOwner->moveSpeed);
			myOwner->damageMultiplier = 1;
		}
	}
	if (dashTime >= 0)
	{
		dashTime -= DeltaTime;
		FVector backward = myOwner->GetActorForwardVector() * -1.f;
		FVector NewLocation;
		NewLocation = myOwner->GetActorLocation();
		NewLocation += (backward * dashSpeed_2 * DeltaTime);
		myOwner->SetActorLocation(NewLocation);
	}
}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void AWaterElement::ability1()
{
	Super::ability1();
	combo = !combo;
}

// Executed through Animation (Check Animation blueprint for the element)
void AWaterElement::ability1FireCode()
{
	myOwner->setRotationRate(myOwner->rotationRate);
	myOwner->setMoveSpeed(myOwner->moveSpeed);
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AWaterElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AWaterElementAbility1>(WaterElementAbility1_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability1Range, myOwner->GetActorRotation(), tempParam);
}

void AWaterElement::ability1End()
{

}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void AWaterElement::ability2()
{
	Super::ability2();
	myOwner->hitAnimImmune = true;
	myOwner->setMoveSpeed(0.f);
	myOwner->currentSpeed = 0.f;
	buffDur = ability2lifeSpan;
}

// Executed through Animation (Check Animation blueprint for the element)
void AWaterElement::ability2FireCode()
{
	AWaterElementAbility2* temp;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	myOwner->stopAllVelocity();
	temp = GetWorld()->SpawnActor<AWaterElementAbility2>(WaterElementAbility2_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector(), myOwner->GetActorRotation(), tempParam);
}

void AWaterElement::ability2End()
{}

void AWaterElement::outputLog()
{
	UE_LOG(LogTemp, Warning, TEXT("Collision on"));
}

int AWaterElement::returnElementType()
{
	Super::returnElementType();
	return 3;
}