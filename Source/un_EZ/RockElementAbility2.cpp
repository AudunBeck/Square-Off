// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElementAbility2.h"
#include "Tori.h"


// Sets default values
ARockElementAbility2::ARockElementAbility2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	Cast<UShapeComponent>(boxCollider)->SetGenerateOverlapEvents(true);
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility2::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ARockElementAbility2::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARockElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (movingTime > 0)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(NewLocation);
		movingTime -= DeltaTime;
	}
}

void ARockElementAbility2::setupAttack(ATori * newOwner, FVector scale, float lifeSpan, float wallSpeed)
{
	myOwner = newOwner;
	//SetActorScale3D(scale);
	SetLifeSpan(lifeSpan);
	speed = wallSpeed;

}

void ARockElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (movingTime > 0)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			ATori* player = Cast<ATori>(OtherActor);
			UE_LOG(LogTemp, Warning, TEXT("PLAYESR IS TOUCHING ME!"));
			player->recieveDamage(10.f, 5 * speed, GetActorLocation());
		}
	}

}

void ARockElementAbility2::moveWall(FVector playerLoc, float punchSpeed)
{
	/// Can update this function to "slowly" turn the wall towards the correct rotation
	punchPos = playerLoc;
	wallPos = this->GetActorLocation();
	FRotator temp = (wallPos - punchPos).Rotation();
	this->SetActorRotation(temp);
	movingTime = maxMovingTime;
	speed *= punchSpeed;
}
