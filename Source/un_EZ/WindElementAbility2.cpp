// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"

AWindElementAbility2::AWindElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility2::OnOverlapBegin);
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	myDistance = myElement->distance;
	myChannelSpeed = myElement->channelSpeed;
	damage = myElement->ability2Damage;
	spawnLocation = GetActorLocation();
}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * myChannelSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	distTraveled = sqrt(pow((spawnLocation.X - NewLocation.X), 2) + pow((spawnLocation.Y - NewLocation.Y), 2));
	if (distTraveled > myDistance)
		this->Destroy();
}

void AWindElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage is: %f"), damage);
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			Cast<ATori>(OtherActor)->recieveDamage(damage);
		}
	}
}
