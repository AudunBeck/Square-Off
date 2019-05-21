#include "WindElementAbility1.h"
#include "RockElementAbility2.h"

AWindElementAbility1::AWindElementAbility1()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
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
	if (myElement->combo == 3)
	{
		damage = myElement->ability1BuffedDamage;
		knockback = myElement->ability1BuffedKnockBack;
	}
	else
	{
		damage = myElement->ability1Damage;
		knockback = myElement->ability1KnockBack;
	}
	spawnLocation = GetActorLocation();
	
	if (myElement->ability1Down)
		direction = FVector(0.f, 0.f, -1.0f);
	else
		direction = myPlayer->GetActorForwardVector();
	collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility1::OnOverlapBegin);
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
			Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage, knockback, myPlayer->GetActorLocation());
			Destroy();

		}

		else if (OtherActor->IsA(ARockElementAbility2::StaticClass()))
		{
			hasHit = true;
			hitEnemyVFX(OtherActor->GetActorLocation());
			Destroy();
		}
	}
}
