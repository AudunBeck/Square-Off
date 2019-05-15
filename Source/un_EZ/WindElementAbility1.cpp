// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility1.h"
#include "RockElementAbility2.h"

AWindElementAbility1::AWindElementAbility1()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

}

void AWindElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	myDistance = myElement->ability1Range;
	myChannelSpeed = myElement->channelSpeed;
	damage = myElement->ability1Damage;
	knockback = myElement->ability1KnockBack;
	spawnLocation = GetActorLocation();
	collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility1::OnOverlapBegin);//Move this to beginPlay()
	//Add this back when we want 4 directions
	if (myElement->ability1Down)
		direction = FVector(0.f, 0.f, -1.0f);
	else
		direction = myPlayer->GetActorForwardVector();

}

void AWindElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += direction * myChannelSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	distTraveled = sqrt(pow((spawnLocation.X - NewLocation.X), 2) + pow((spawnLocation.Y - NewLocation.Y), 2));
	if (distTraveled > myDistance)
		this->Destroy();
}

void AWindElementAbility1::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			ccDur = 2/*myElement->maxInterval*/;
			playerLocation = myPlayer->GetActorLocation();
			enemyLocation = OtherActor->GetActorLocation();
			enemyForward = OtherActor->GetActorForwardVector();

			a = (playerLocation - enemyLocation).GetSafeNormal();
			b = enemyForward.GetSafeNormal();
			float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(a, b)));
			slow = (angle - 90) / 3;		// 3 is a covalent, which can be increased to degress the slow, and vise-versa

			if (myElement->combo == 3)
				Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage, knockback, myPlayer->GetActorForwardVector());
			else
				Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage);

			//Cast<ATori>(OtherActor)->LaunchCharacter(myPlayer->GetActorForwardVector() * 300.f, false, true);
		}
		else if (OtherActor->IsA(ARockElementAbility2::StaticClass()))
		{
			hasHit = true;
			hitEnemyVFX(OtherActor->GetActorLocation());
			Destroy();
		}
	}
}
