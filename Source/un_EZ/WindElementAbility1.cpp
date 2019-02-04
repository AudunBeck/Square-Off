// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility1.h"

// Sets default values
AWindElementAbility1::AWindElementAbility1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility1::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AWindElementAbility1::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWindElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * boltSpeed * DeltaTime;
	SetActorLocation(NewLocation);

}

void AWindElementAbility1::setupAttack(ATori * newOwner, float lifeSpan, float boltSpeedIn, float damageIn)
{
	myPlayer = newOwner;
	SetLifeSpan(lifeSpan);
	boltSpeed = boltSpeedIn;
	damage = damageIn;
}

void AWindElementAbility1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			// Make the target take damage
			//Cast<ATori>(OtherActor)->recieveDamage(damage, ccDur, slow, 0);	// float value 0 is slow
		}
	}
}