// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnInpact.h"

// Sets default values
ASpawnInpact::ASpawnInpact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider")); // Can change USphereComponent to Mesh
//RootComponent = collider;
	collider->SetupAttachment(RootComponent);
	Cast<UShapeComponent>(collider)->SetGenerateOverlapEvents(false);
	Cast<UShapeComponent>(collider)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnInpact::OnOverlapBegin);
	RootComponent = collider;
}

// Called when the game starts or when spawned
void ASpawnInpact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnInpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnInpact::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor != myPlayer)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				// Make the target take damage
				Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage);
				Cast<ATori>(OtherActor)->LaunchCharacter((Cast<ATori>(OtherActor)->GetActorLocation()) - (GetActorLocation()), true, true);
				myPlayer->freezeFrame(0.15, false);
			}
		}
	}
}

