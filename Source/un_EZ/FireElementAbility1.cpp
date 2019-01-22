// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElementAbility1.h"

// Sets default values
AFireElementAbility1::AFireElementAbility1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AFireElementAbility1::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AFireElementAbility1::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFireElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->SetActorLocation(myOwner->GetActorForwardVector() * 100.f + myOwner->GetActorLocation());
}

void AFireElementAbility1::setupAttack(ATori* newOwner, float lifeSpan)
{
	myOwner = newOwner;
	SetLifeSpan(lifeSpan);
}

void AFireElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (buffed)
	{
		if (OtherActor != myOwner)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				// Make the target take damage
				Cast<ATori>(OtherActor)->recieveDamage(30.f);	// float value is temporary

				/// Change this to its own effect-class
				// Do some crazy shit
			}
		}
	}
	if (!buffed)
	{
		if (OtherActor != myOwner)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				// Make the target take damage
				Cast<ATori>(OtherActor)->recieveDamage(30.f);	// float value is temporary
			}
		}
	}


}