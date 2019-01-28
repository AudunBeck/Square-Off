// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"

AWindElementAbility2::AWindElementAbility2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility2::OnOverlapBegin);
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();

}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWindElementAbility2::setupAttack(ATori * newOwner, AWindElement * myElementIn, float lifeSpan, float dashDistIn, float ccDurIn, float slowIn, float damageIn)
{
	myOwner = newOwner;
	myElement = myElementIn;
	SetLifeSpan(lifeSpan);
	dashDist = dashDistIn;
	ccDur = ccDurIn;
	slow = slowIn;
	damage = damageIn;
}

void AWindElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!OtherActor->IsA(AWindElementAbility2::StaticClass()))
	{
		if (OtherActor->IsA(ABaseAbility::StaticClass()))
		{
			if (myElement != nullptr)
			{
				if (myOwner != nullptr)
				{
				//	myElement->buffDur = 0.f;
				//	if (myElement->buffDur == 0.f)
				//	{
				//		ATori* enemy = Cast<ABaseAbility>(OtherActor)->getMyOwner();
				//		FVector enemyLocation = enemy->GetActorLocation();
				//		FVector ownerLocation = myOwner->GetActorLocation();
				//		FVector launchDirection = enemyLocation - ownerLocation;
				//		UE_LOG(LogTemp, Warning, TEXT("Countered an attack!"));
				//		myOwner->LaunchCharacter(myOwner->GetActorForwardVector() * dashDist, true, true);
				//		enemy->recieveDamage(damage, ccDur, slow, 0);
				//		myOwner->locked = 0.f;

				//	}
				//}
			}
		}
	}
}
