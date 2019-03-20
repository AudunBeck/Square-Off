// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElementAbility2.h"
#include "Tori.h"
#include "Engine/BlockingVolume.h"

ARockElementAbility2::ARockElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	Cast<UShapeComponent>(boxCollider)->SetGenerateOverlapEvents(true);
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility2::OnOverlapBegin);
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &ARockElementAbility2::EndOnOverlap);

}

void ARockElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<ARockElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability2Lifespan);
	speed = myElement->ability2Speed;
	damageDivision = speed;
	playerKnockback = myElement->ability2KnockbackMulti;
	damage = myElement->ability2Damage;
	hangTime = maxHangTime;
}

void ARockElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(hangTime >= 0)
		hangTime -= DeltaTime;
	if (isTouchingGround == false && hangTime < 0)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * -1 * speed * DeltaTime;
		SetActorLocation(NewLocation);
	}
	if (movingTime > 0)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(NewLocation);
		movingTime -= DeltaTime;
		if (hitPlayer)
		{
			hitPlayer->recieveDamage(damage * (speed / damageDivision), playerKnockback * speed, GetActorLocation());
			movingTime = 0.f;
			hitPlayer = nullptr;
		}
	}
}

void ARockElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA(ATori::StaticClass()))
	{
		hitPlayer = Cast<ATori>(OtherActor);
	}
	if (movingTime > 0 || !isTouchingGround)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			hitPlayer = Cast<ATori>(OtherActor);
			hitPlayer->recieveDamage(damage * (speed / damageDivision), playerKnockback * speed, GetActorLocation());
			movingTime = 0.f;
			hitPlayer = nullptr;
		}
		else if(OtherActor->IsA(ABlockingVolume::StaticClass()) || OtherActor->IsA(ARockElementAbility2::StaticClass()))
		{
			movingTime = 0.f;
		}
	}
}

void ARockElementAbility2::EndOnOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == hitPlayer)
		hitPlayer = nullptr;
}

void ARockElementAbility2::moveWall(FRotator playerRot, float punchSpeed)
{
	FRotator temp = playerRot;
	this->SetActorRotation(temp);
	movingTime = maxMovingTime;
	speed *= punchSpeed;
}
