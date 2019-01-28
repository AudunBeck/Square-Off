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

void AWindElementAbility2::setupAttack(ATori * newOwner, AWindElement * myElementIn, float lifeSpan, float damageIn, float innerRadiusIn, float outerRadiusIn)
{
	myOwner = newOwner;
	myElement = myElementIn;
	SetLifeSpan(lifeSpan);
	damage = damageIn;
	innerRadius = innerRadiusIn;
	outerRadius = outerRadiusIn;
	collider->SetSphereRadius(outerRadius);
}

void AWindElementAbility2::checkForEnemy()
{
	enemyReference = nullptr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATori::StaticClass(), enemy);
	numOfEnemy = enemy.Num();
	if (numOfEnemy > 0)
	{
		for (int i = 1; i <= numOfEnemy; i++)
		{
			playerLocation = myOwner->GetActorLocation();
			enemyReference = Cast<ATori>(enemy[i]);
			enemyLocation = enemyReference->GetActorLocation();
			RadiusToEnemy = sqrt(pow((enemyLocation.X - playerLocation.X), 2) + pow((enemyLocation.Y - playerLocation.Y), 2));
			if (RadiusToEnemy < outerRadius)
			{
				// Do stuff
			}
		}
	}


}

void AWindElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	// if(counter == 3) --> PushBack i tillegg, type "enemy->LaunchCharacter"

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
				}
			}
		}
	}
}
