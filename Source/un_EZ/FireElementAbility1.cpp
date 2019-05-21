#include "FireElementAbility1.h"

AFireElementAbility1::AFireElementAbility1()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	collider->SetupAttachment(RootComponent);
	Cast<UShapeComponent>(collider)->SetGenerateOverlapEvents(false);
	Cast<UShapeComponent>(collider)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RootComponent = collider;
}

void AFireElementAbility1::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AFireElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability1lifeSpan);
	attackRange = myElement->ability1Range;
	if (myElement->fireChi >= 1)
	{
		buffed = true;
		damage = myElement->ability1BuffedDamage;
		knockback = myElement->ability1BuffedKnockback;
		SetActorScale3D(myElement->boostedAbility1Scale);
		myElement->fireChi = 0;
	}
	else
	{
		damage = myElement->ability1Damage;
		knockback = myElement->ability1Knockback;
		buffed = false;
	}
	beginSound();
	Cast<UShapeComponent>(collider)->SetGenerateOverlapEvents(true);
	forward = myPlayer->GetActorForwardVector();
	myPlayer->forceMove(forward, myElement->launchSpeed_1, GetLifeSpan());
	collider->OnComponentBeginOverlap.AddDynamic(this, &AFireElementAbility1::OnOverlapBegin);
}

void AFireElementAbility1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetActorLocation(forward * attackRange + myPlayer->GetActorLocation());
	this->SetActorRotation(myPlayer->GetActorRotation());
}

void AFireElementAbility1::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex,bFromSweep, SweepResult);
	if (!hasHit)
	{
		if (OtherActor != myPlayer)
		{
			if (OtherActor->IsA(ATori::StaticClass()))
			{
				Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage, knockback, myPlayer->GetActorLocation());
				if (!buffed)
					myElement->fireChi += 1;
				hitEnemyVFX(OtherActor->GetActorLocation());
				myPlayer->freezeFrame(0.15, false);
				myPlayer->stopAllVelocity();
				myElement->abilityHit = true;
				hasHit = true;
				myPlayer->forceMove();
				myElement->ability1HitAnim();
			}
		}
	}
}
