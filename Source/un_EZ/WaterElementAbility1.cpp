// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElementAbility1.h"

// Sets default values
AWaterElementAbility1::AWaterElementAbility1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AWaterElementAbility1::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AWaterElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * boltSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	/// Add so that the first few frames, the waterbolt goes slow and afterwards go fast - Make bool so we can add (potentially) own animation to go along
}

void AWaterElementAbility1::setupAttack(ATori * newOwner, float lifeSpan, float boltSpeedIn, float ccDurIn, float slowIn, float damageIn)
{
	myPlayer = newOwner;
	SetLifeSpan(lifeSpan);
	boltSpeed = boltSpeedIn;
	ccDur = ccDurIn;
	slow = slowIn;
	damage = damageIn;
}

void AWaterElementAbility1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			// Make the target take damage
			Cast<ATori>(OtherActor)->recieveDamage(damage, ccDur, slow, 0);	// float value 0 is slow
		}
	}
}

