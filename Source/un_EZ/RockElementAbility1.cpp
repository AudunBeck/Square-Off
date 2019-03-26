// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElementAbility1.h"
#include "RockElementAbility2.h"

ARockElementAbility1::ARockElementAbility1()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility1::OnOverlapBegin);
}

void ARockElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner() != nullptr)
		myElement = Cast<ARockElement>(GetOwner());
	if (myElement != nullptr)
		myPlayer = myElement->getMyOwner();
	chargedHit = myElement->chargeFloat;
	SetLifeSpan((myElement->ability1lifeSpan) * chargedHit);
	attackRange = myElement->ability1Range;
	damage = myElement->ability1Damage;
}

void ARockElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (myPlayer != nullptr)
	this->SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
}

void ARockElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage);
			myPlayer->stopAllVelocity();
			myPlayer->freezeFrame(0.15, false);
			myPlayer->setRotationRate(myPlayer->rotationRate);
			hitEnemyVFX(OtherActor->GetActorLocation());
			Destroy();
		}

		if (OtherActor->IsA(ARockElementAbility2::StaticClass()))
		{

			if (myPlayer != nullptr)
			{
				myPlayer->freezeFrame(0.15, false);
				FRotator temp = FRotator(myPlayer->GetActorRotation());
				Cast<ARockElementAbility2>(OtherActor)->moveWall(temp, chargedHit);
				hitEnemyVFX(OtherActor->GetActorLocation());
				myPlayer->setRotationRate(myPlayer->rotationRate);
				Destroy();
			}
			else
			{
				myPlayer->freezeFrame(0.15, false);
				UE_LOG(LogTemp, Warning, TEXT("Punch did not find myPlayer"));
				Cast<ARockElementAbility2>(OtherActor)->moveWall(myPlayer->GetActorRotation(), chargedHit);
				hitEnemyVFX(OtherActor->GetActorLocation());
				myPlayer->setRotationRate(myPlayer->rotationRate);
			}
		}
	}

}
