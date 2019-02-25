// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility1.h"

AWindElementAbility1::AWindElementAbility1()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility1::OnOverlapBegin);
}

void AWindElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability1lifeSpan);
	boltSpeed = myElement->boltSpeed;
	damage = myElement->ability1damage;
	range = myElement->range;
	spawnLocation = GetActorLocation();
}

void AWindElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * boltSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	distTraveled = sqrt(pow((spawnLocation.X - NewLocation.X), 2) + pow((spawnLocation.Y - NewLocation.Y), 2));
	if (distTraveled > range)
		this->Destroy();

}

void AWindElementAbility1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			Cast<ATori>(OtherActor)->recieveDamage(damage);
		}
	}
}