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
}

void AWaterElementAbility2::setupAttack(AWaterElement* myElementIn, float lifeSpan, float dashDistIn, float ccDurIn, float slowIn, float damageIn)
{
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
	if (myOwner != nullptr)
		if (myElement != nullptr)
			if (OtherActor != myElement)
				if (OtherActor->IsA(ABaseAbility::StaticClass()))
				{
					UE_LOG(LogTemp, Warning, TEXT("Countered an attack!"));
					ATori* Enemy = Cast<ABaseAbility>(OtherActor)->getMyOwner();
					myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * dashDist, false, true);
					Enemy->recieveDamage(damage, ccDur, slow, 0);
					myElement->counter = 3;
				}
}