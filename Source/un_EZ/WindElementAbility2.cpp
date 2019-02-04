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

	//collider->OnComponentBeginOverlap.AddDynamic(this, &AWindElementAbility2::OnOverlapBegin);
	
}

void AWindElementAbility2::BeginPlay()
{
	Super::BeginPlay();

}

void AWindElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentTime += DeltaTime;
	checkForEnemy();
}

void AWindElementAbility2::setupAttack(ATori * newOwner, AWindElement * myElementIn, float lifeSpan, float damageIn, float innerRadiusIn, float outerRadiusIn)
{
	myPlayer = newOwner;
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
	numOfEnemy = enemy.Num() -1;
	if (numOfEnemy > 0)
	{
		for (int i = 0; i <= numOfEnemy; i++)
		{
			playerLocation = myPlayer->GetActorLocation();
			enemyReference = Cast<ATori>(enemy[i]);
			enemyLocation = enemyReference->GetActorLocation();

		}
	}


}
