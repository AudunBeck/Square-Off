// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElementAbility1.h"
#include "RockElementAbility2.h"

// Sets default values
ARockElementAbility1::ARockElementAbility1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility1::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ARockElementAbility1::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARockElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->SetActorLocation(myOwner->GetActorForwardVector() * attackRange + myOwner->GetActorLocation());
}

void ARockElementAbility1::setupAttack(ATori* newOwner, float lifeSpan, float range, float chargeFloat)
{
	myOwner = newOwner;
	SetLifeSpan(lifeSpan);
	attackRange = range;
	chargedHit = chargeFloat;
}

void ARockElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != myOwner)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			// Make the target take damage	
			Cast<ATori>(OtherActor)->recieveDamage(30.f * chargedHit);	// float value is temporary
		}

		if (OtherActor->IsA(ARockElementAbility2::StaticClass()))
		{
			FVector temp(0,0,0);
			if (myOwner != nullptr)
				temp= FVector(myOwner->GetActorLocation());
			Cast<ARockElementAbility2>(OtherActor)->moveWall(temp);
		}
	}

}