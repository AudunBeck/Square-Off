// Fill out your copyright notice in the Description page of Project Settings.

#include "WaterElementAbility2.h"
#include "WaterElement.h"

// Sets default values
AWaterElementAbility2::AWaterElementAbility2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AWaterElementAbility2::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AWaterElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWaterElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability2lifeSpan);
	dashDist = myElement->dashDist;
	ccDur = myElement->ability2CcDur;
	slow = myElement->ability2Slow;
	damage = myElement->ability2Damage;
}

// Called every frame
void AWaterElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(myPlayer)
		this->SetActorLocation(myPlayer->GetActorLocation());
	if (myElement == nullptr)
		UE_LOG(LogTemp, Error, TEXT("MyElement is nullptr - Check WaterElementAbilit2.cpp - setupAttack()"))
}

void AWaterElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!OtherActor->IsA(AWaterElementAbility2::StaticClass()))
	{
		if (OtherActor->IsA(ABaseAbility::StaticClass()))
		{
			if (myElement != nullptr)
			{
				if (myPlayer != nullptr)
				{
					myElement->buffDur = 0.f;
					if (myElement->buffDur == 0.f)
					{
						ATori* enemy = Cast<ABaseAbility>(OtherActor)->getMyOwner();
						FVector enemyLocation = enemy->GetActorLocation();
						FVector ownerLocation = myPlayer->GetActorLocation();
						FVector launchDirection = enemyLocation - ownerLocation;
						myPlayer->LaunchCharacter(myPlayer->GetActorForwardVector() * dashDist, false, true);
						enemy->recieveDamage(damage, ccDur, slow, 0);
						myPlayer->locked = 0.f;
						myPlayer->setMoveSpeed(myPlayer->moveSpeed);
						myElement->counter = 3;
					}
				}
			}
		}
	}
}
