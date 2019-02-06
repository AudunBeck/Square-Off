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
	myElement = Cast<AFireElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability1lifeSpan);
	attackRange = myElement->ability1Range;
	damage = myElement->ability1Damage;
	if (myElement->fireChi > 0)
	{
		damage = myElement->ability1BuffedDamage;
		SetActorScale3D(myElement->boostedAbility1Scale);
	}
}

// Called every frame
void AFireElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
	this->SetActorRotation(myPlayer->GetActorRotation());
}

void AFireElementAbility1::setupAttack(ATori* newOwner, float lifeSpan, float range, FVector scale)
{

}

void AFireElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (buffed)
	{
		if (OtherActor != myPlayer)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				// Make the target take damage
				Cast<ATori>(OtherActor)->recieveDamage(damage);	// float value is temporary
				/// Change this to its own effect-class
				// Do some crazy shit
				myPlayer->stopAllVelocity();

			}
		}
	}
	if (!buffed)
	{
		if (OtherActor != myPlayer)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				// Make the target take damage
				Cast<ATori>(OtherActor)->recieveDamage(damage);	// float value is temporary
				myPlayer->stopAllVelocity();
			}
		}
	}


}