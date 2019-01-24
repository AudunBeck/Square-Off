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
}

// Called every frame
void AWaterElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(myOwner)
		this->SetActorLocation(myOwner->GetActorLocation());
	if (myElement == nullptr)
		UE_LOG(LogTemp, Error, TEXT("MyElement is nullptr - Check WaterElementAbilit2.cpp - setupAttack()"))
}

void AWaterElementAbility2::setupAttack(ATori * newOwner, AWaterElement* myElementIn, float lifeSpan, float dashDistIn, float ccDurIn, float slowIn, float damageIn)
{
	myOwner = newOwner;
	myElement = myElementIn;
	SetLifeSpan(lifeSpan);
	dashDist = dashDistIn;
	ccDur = ccDurIn;
	slow = slowIn;
	damage = damageIn;
}
void AWaterElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("Counter attack"));
	if (OtherActor->IsA(ABaseAbility::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("OtherActor is baseability"));
		if (OtherActor != myElement)
		{
			UE_LOG(LogTemp, Error, TEXT("OtherActor != myElement"));
			if (myElement != nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("MyElement != nullptr"));
				if (myOwner != nullptr)
				{
					ATori* enemy = Cast<ABaseAbility>(OtherActor)->getMyOwner();
					FVector enemyLocation = enemy->GetActorLocation();
					FVector ownerLocation = myOwner->GetActorLocation();
					FVector launchDirection = enemyLocation - ownerLocation;
					UE_LOG(LogTemp, Warning, TEXT("Countered an attack!"));
					myOwner->LaunchCharacter(launchDirection * dashDist, false, false);
					enemy->recieveDamage(damage, ccDur, slow, 0);
					myElement->counter = 3;
					myElement->buffDur = 0.f;
				}
			}
				
		}
			
	}
		
}