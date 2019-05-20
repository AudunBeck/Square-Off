#include "FireElement.h"
#include "ConstructorHelpers.h"
#include "FireElementStruct.h"

AFireElement::AFireElement()
{

	static ConstructorHelpers::FObjectFinder<UDataTable>
		FireElementTable(TEXT("DataTable'/Game/DataTables/FireElementTable.FireElementTable'"));
	BalancingTable = FireElementTable.Object;

	//Searching and getting data
	FFireElementStruct* Ability1Data = BalancingTable->FindRow<FFireElementStruct>(FName("1"), FString(""));
	FFireElementStruct* Ability2Data = BalancingTable->FindRow<FFireElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		ability1Damage = Ability1Data->Damage;
		ability1BuffedDamage = Ability1Data->BuffedDamage;
		ability1Range = Ability1Data->Range;
		launchSpeed_1 = Ability1Data->MoveRange;
		ability1Knockback = Ability1Data->Knockback;
		ability1lifeSpan = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		maxFireChi = Ability2Data->BuffedDamage;
		ability2Range = Ability2Data->Range;
		launchSpeed_2 = Ability2Data->MoveRange;
		ability2Lifespan = Ability2Data->LifeSpan;
	}
}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void AFireElement::ability1()
{
	if (myOwner->ability1Ended == false)
	{
		Super::ability1();
	}
}

// Executed through Animation (Check Animation blueprint for the element)
void AFireElement::ability1FireCode()
{
	abilityHit = false;
	FVector tempDir = myOwner->facingDirection;
	tempDir.Normalize();
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AFireElementAbility1* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility1>(FireElementAbility1_BP,
		myOwner->GetActorLocation() + tempDir * ability1Range, myOwner->GetActorRotation(), tempParam);
}

void AFireElement::ability1End()
{}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void AFireElement::ability2()
{
	if (myOwner->ability2Ended == false)
	{
		Super::ability2();
		myOwner->locked = true;
		myOwner->setMoveSpeed(0);
	}
}

// Executed through Animation (Check Animation blueprint for the element)
void AFireElement::ability2FireCode()
{
	myOwner->setRotationRate(0);
	abilityHit = false;

	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	AFireElementAbility2* temp;
	temp = GetWorld()->SpawnActor<AFireElementAbility2>(FireElementAbility2_BP,
		myOwner->GetActorLocation() + myOwner->GetActorForwardVector() * ability2Range, myOwner->GetActorRotation(), tempParam);
}

void AFireElement::ability2End()
{}

int AFireElement::returnElementType()
{
	Super::returnElementType();
	return 2;
}

void AFireElement::BeginPlay()
{
	Super::BeginPlay();
	attachFireEmitters();
}
