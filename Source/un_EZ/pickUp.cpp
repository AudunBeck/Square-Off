#include "pickUp.h"
#include "Tori.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "pickUpSpawner.h"

ApickUp::ApickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Cast<UShapeComponent>(collider)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(collider)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->SetupAttachment(RootComponent);
}

void ApickUp::BeginPlay()
{
	Super::BeginPlay();

	collider->OnComponentBeginOverlap.AddDynamic(this, &ApickUp::OnOverlapBegin);
	collider->OnComponentEndOverlap.AddDynamic(this, &ApickUp::OnOverlapEnd);
}

void ApickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ApickUp::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATori::StaticClass()))
	{
		if (ElementBlueprint != nullptr)
		{
			ATori* player = Cast<ATori>(OtherActor);
			player->currentPickUp = this;
		}
	}
}

void ApickUp::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATori::StaticClass()))
	{
		ATori* player = Cast<ATori>(OtherActor);
		player->currentPickUp = nullptr;
	}
}

void ApickUp::giveElement(ATori * player)
{
	FActorSpawnParameters tempParam;
	tempParam.Owner = player;
	ABaseElement* temp = GetWorld()->SpawnActor<ABaseElement>(ElementBlueprint, tempParam);
	if (player->pickUpElement(temp))
	{
		if (mySpawner != nullptr)
			mySpawner->elementPickedUp();
		StartDestroy();
	}
	else
	{
		temp->Destroy();
	}
}
