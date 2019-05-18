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
}

void ARockElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<ARockElement>(GetOwner());
	myPlayer = myElement->myOwner;
	//SetLifeSpan(myElement->ability2Lifespan);
	lifespan = myElement->ability2Lifespan;
	speed = myElement->ability2Speed;
	damageDivision = speed;
	playerKnockback = myElement->ability2KnockbackMulti;
	damage = myElement->ability2Damage;
	hangTime = maxHangTime;
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility2::OnOverlapBegin);
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &ARockElementAbility2::EndOnOverlap);
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
			hitPlayer->recieveDamage(myPlayer, damage), playerKnockback, GetActorLocation());
			movingTime = 0.f;
			hitPlayer = nullptr;
		}
	}
	
	if (lifespan > 0.f)
	{
		lifespan -= DeltaTime;
		if (lifespan <= 0.f && !startedDestroy)
		{
			StartDespawn();
			startedDestroy = true;
		}
	}
}

void ARockElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!hasHit)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			hitPlayer = Cast<ATori>(OtherActor);
			hasHit = true;
		}
		if (movingTime > 0 || !isTouchingGround)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				hitPlayer = Cast<ATori>(OtherActor);
				hitPlayer->recieveDamage(myPlayer, damage, playerKnockback, GetActorLocation());
				movingTime = 0.f;
				hitPlayer = nullptr;
				hasHit = true;
				StartDestroy();
				startedDestroy = true;
			}
			else if (OtherActor->IsA(ABlockingVolume::StaticClass()) || OtherActor->IsA(ARockElementAbility2::StaticClass()))
			{
				movingTime = 0.f;
			}
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
	moveAnim();
}
