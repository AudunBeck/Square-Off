// Fill out your copyright notice in the Description page of Project Settings.

#include "WindElementAbility2.h"

AWindElementAbility2::AWindElementAbility2()
{
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
	myElement = Cast<AWindElement>(GetOwner());
	myPlayer = myElement->myOwner;
	myDistance = myElement->distance;
	myChannelSpeed = myElement->channelSpeed;
	damage = myElement->ability2Damage;
	spawnLocation = GetActorLocation();
}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * myChannelSpeed * DeltaTime;
	SetActorLocation(NewLocation);
	distTraveled = sqrt(pow((spawnLocation.X - NewLocation.X), 2) + pow((spawnLocation.Y - NewLocation.Y), 2));
	if (distTraveled > myDistance)
		this->Destroy();
}

void AWindElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
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
			slow = 30.f; //(50 * (b.Size() / a.Size()));

			float angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(a, b)));
			float sin;
			float cos;
			FMath::SinCos(&sin, &cos, angle);
			UE_LOG(LogTemp, Warning, TEXT("Angle is: %f"), angle);
			UE_LOG(LogTemp, Warning, TEXT("Sine is: %f"), sin);
			UE_LOG(LogTemp, Warning, TEXT("cos is: %f"), cos);

			Cast<ATori>(OtherActor)->recieveDamage(damage, ccDur, slow, 0);
			
			//Cast<ATori>(OtherActor)->LaunchCharacter(myPlayer->GetActorForwardVector() * 300.f, false, true);
		}
	}
}
