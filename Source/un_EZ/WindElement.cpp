#include "WindElement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ConstructorHelpers.h"
#include "WindElementStruct.h"
AWindElement::AWindElement()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable>
		WindElementTable(TEXT("DataTable'/Game/DataTables/WindElementTable.WindElementTable'"));
	BalancingTable = WindElementTable.Object;

	//Searching and getting data
	FWindElementStruct* Ability1Data = BalancingTable->FindRow<FWindElementStruct>(FName("1"), FString(""));
	FWindElementStruct* Ability2Data = BalancingTable->FindRow<FWindElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		ability1Damage = Ability1Data->Damage;
		ability1BuffedDamage = Ability1Data->BuffedDamage;
		ability1Range = Ability1Data->Range;
		channelSpeed = Ability1Data->MoveRange;
		ability1KnockBack = Ability1Data->Knockback;
		ability1BuffedKnockBack = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{		
		ability2Damage = Ability2Data->Damage;
		ability2Gravity = Ability2Data->BuffedDamage;
		ability2Radius = Ability2Data->Range;
		bonusSpeed = Ability2Data->MoveRange;
		ability2KnockBack = Ability2Data->Knockback;
		ability2Lifespan = Ability2Data->LifeSpan;
	}
}

void AWindElement::BeginPlay()
{
	Super::BeginPlay();
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void AWindElement::ability1()
{
	Super::ability1();
}

// Executed through Animation (Check Animation blueprint for the element)
void AWindElement::ability1FireCode()
{
	combo += 1;
	AWindElementAbility1* temp;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
		myOwner->GetActorRotation(), tempParam);

}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void AWindElement::ability2()
{
	if (!windUsingAbility2)
	{
		AWindElementAbility2* temp;
		FActorSpawnParameters tempParam;
		tempParam.Owner = this;
		temp = GetWorld()->SpawnActor<AWindElementAbility2>(WindElementAbility2_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
			myOwner->GetActorRotation(), tempParam);
		ability2PullParticle();
	}
}

// Executed through Animation (Check Animation blueprint for the element)
void AWindElement::ability2FireCode()
{}

int AWindElement::returnElementType()
{
	Super::returnElementType();
	return 4;
}
