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
	forward = myPlayer->GetActorForwardVector();
	myPlayer->forceMove(forward, myElement->launchSpeed_1, GetLifeSpan());
	knockback = myElement->ability1Knockback;
	collider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility1::OnOverlapBegin);//Move this to beginPlay()

}

void ARockElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
}

void ARockElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!hasHit)
	{
		if (OtherActor != myPlayer)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage, knockback, myPlayer->GetActorLocation());
				myPlayer->forceMove();
				myPlayer->stopAllVelocity();
				myPlayer->freezeFrame(0.15, false);
				myPlayer->setRotationRate(myPlayer->rotationRate);
				hitEnemyVFX(OtherActor->GetActorLocation());
				myElement->ability1PunchAnim();
				hasHit = true;
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
					myElement->ability1PunchAnim();
					hasHit = true;
				}
				else
				{
					myPlayer->freezeFrame(0.15, false);
					UE_LOG(LogTemp, Warning, TEXT("Punch did not find myPlayer"));
					Cast<ARockElementAbility2>(OtherActor)->moveWall(myPlayer->GetActorRotation(), chargedHit);
					hitEnemyVFX(OtherActor->GetActorLocation());
					myPlayer->setRotationRate(myPlayer->rotationRate);
					myElement->ability1PunchAnim();
					hasHit = true;
				}
			}
		}
	}

}
