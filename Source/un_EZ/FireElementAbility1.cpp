// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElementAbility1.h"

AFireElementAbility1::AFireElementAbility1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider")); // Can change USphereComponent to Mesh
	//RootComponent = collider;
	collider->SetupAttachment(RootComponent);
	Cast<UShapeComponent>(collider)->SetGenerateOverlapEvents(false);
	Cast<UShapeComponent>(collider)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AFireElementAbility1::OnOverlapBegin);
}

void AFireElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AFireElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability1lifeSpan);
	attackRange = myElement->ability1Range;
	if (myElement->fireChi >= 2)
	{
		buffed = true;
		damage = myElement->ability1BuffedDamage;
		SetActorScale3D(myElement->boostedAbility1Scale);
		myElement->fireChi = 0;
	}
	else
	{
		damage = myElement->ability1Damage;
		buffed = false;
	}
	beginSound();
	Cast<UShapeComponent>(collider)->SetGenerateOverlapEvents(true);
}

void AFireElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
	this->SetActorRotation(myPlayer->GetActorRotation());
}

void AFireElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			// Make the target take damage
			Cast<ATori>(OtherActor)->recieveDamage(damage);
			if (!buffed)
				myElement->fireChi += 1;
			hitEnemyVFX(OtherActor->GetActorLocation());
			myPlayer->freezeFrame(0.15, false);
			myPlayer->stopAllVelocity();
			myElement->abilityHit = true;
			Destroy();
		}
	}
}
