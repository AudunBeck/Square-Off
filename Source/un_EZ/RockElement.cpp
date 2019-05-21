#include "RockElement.h"
#include "ConstructorHelpers.h"
#include "RockElementStruct.h"

ARockElement::ARockElement()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
		RockElementTable(TEXT("DataTable'/Game/DataTables/RockElementTable.RockElementTable'"));
	BalancingTable = RockElementTable.Object;
	
	//Searching and getting data
	FRockElementStruct* Ability1Data = BalancingTable->FindRow<FRockElementStruct>(FName("1"), FString(""));
	FRockElementStruct* Ability2Data = BalancingTable->FindRow<FRockElementStruct>(FName("2"), FString(""));
	if (Ability1Data)
	{
		ability1Damage = Ability1Data->Damage;
		ability1Range = Ability1Data->Range;
		launchSpeed_1 = Ability1Data->MoveRange;
		ability1Knockback = Ability1Data->KnockBack;
		ability1lifeSpan = Ability1Data->LifeSpan;
	}
	if (Ability2Data)
	{
		ability2Damage = Ability2Data->Damage;
		ability2Range = Ability2Data->Range;
		ability2Speed = Ability2Data->MoveRange;
		ability2KnockbackMulti = Ability2Data->KnockBack;
		ability2Lifespan = Ability2Data->LifeSpan;
	}
}

void ARockElement::BeginPlay()
{
	Super::BeginPlay();
}

void ARockElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (cooldown > 0)
		cooldown -= DeltaTime;

	if (channelingAbility1 == true)
	{
		if (chargeFloat < maxCharge)
		{
			if (chargeFloat > maxCharge)
				chargeFloat = maxCharge;
		}
	}
	if (channelingAbility1 == false && chargeFloat > 0)
	{
		// Reset parameters if needed - Else remove this if-statement
	}
}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void ARockElement::ability1()
{
	myOwner->damageMultiplier = damageReduction;
	myOwner->setMoveSpeed(myOwner->moveSpeed * slowFactor);
	myOwner->currentSpeed = myOwner->moveSpeed * slowFactor;
	myOwner->ability1Used = true;
	myOwner->hitAnimImmune = true;

	Super::ability1();
}

// Executed through Animation (Check Animation blueprint for the element)
void ARockElement::ability1FireCode()
{
	ARockElementAbility1* temp;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	temp = GetWorld()->SpawnActor<ARockElementAbility1>(RockElementAbility1_BP, myOwner->GetActorLocation() + (myOwner->GetActorForwardVector()),
		myOwner->GetActorRotation(), tempParam);
	myOwner->setMoveSpeed(0);
	myOwner->currentSpeed = myOwner->moveSpeed;
	myOwner->setRotationRate(0);
	myOwner->damageMultiplier = 1;
	myOwner->hitAnimImmune = false;
}


void ARockElement::ability1End()
{
	myOwner->ability1Used = false;
	stopLoopAnim();
}

// Executed on keypress event (Check ATori::SetupPlayerInputComponent() in Tori.cpp)
void ARockElement::ability2()
{
	if (myOwner->ability2Ended == false && cooldown <= 0)
	{
		Super::ability2();
		cooldown = ability2Lifespan;
	}
}

// Executed through Animation (Check Animation blueprint for the element)
void ARockElement::ability2FireCode()
{
	FVector forwardVec = myOwner->GetActorForwardVector();
	FVector playerVec = myOwner->GetActorLocation();
	FRotator playerRot = myOwner->GetActorRotation();
	const FVector newVec = (forwardVec * ability2Range) + playerVec;
	FActorSpawnParameters tempParam;
	tempParam.Owner = this;
	ARockElementAbility2* temp = GetWorld()->SpawnActor<ARockElementAbility2>(RockElementAbility2_BP, newVec, playerRot, tempParam);
}


int ARockElement::returnElementType()
{
	Super::returnElementType();
	return 1;
}