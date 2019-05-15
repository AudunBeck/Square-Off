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
	}
	if (Ability2Data)
	{

	}
}

void AWindElement::BeginPlay()
{
	Super::BeginPlay();
	channelTime = 0;
	maxChannelTime = maxInterval * 3;
}

void AWindElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AWindElement::ability1()
{
	Super::ability1();
}


void AWindElement::ability1FireCode()
{
	AWindElementAbility1* temp;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	temp = GetWorld()->SpawnActor<AWindElementAbility1>(WindElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
		myOwner->GetActorRotation(), tempParam);
	combo += 1;
}

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

void AWindElement::ability2FireCode()
{}

int AWindElement::returnElementType()
{
	Super::returnElementType();
	return 4;
}
