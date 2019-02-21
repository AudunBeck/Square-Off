// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElementAbility2.h"

// Sets default values
AFireElementAbility2::AFireElementAbility2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AFireElementAbility2::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFireElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AFireElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability2Lifespan);
	attackRange = myElement->ability2Range;
	damage = myElement->ability2Damage;
}

// Called every frame
void AFireElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sets the hitbox ahead of the player while flying forward
	this->SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
	this->SetActorRotation(myPlayer->GetActorRotation());
}

void AFireElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			// Make the target take damage
			Cast<ATori>(OtherActor)->recieveDamage(damage);	// float value is temporary
			myPlayer->stopAllVelocity();
			myElement->fireChi = 2;
		}
	}
}

