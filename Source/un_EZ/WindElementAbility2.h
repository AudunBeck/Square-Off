// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility2.generated.h"

class AWindElement;
class ATori;

UCLASS()
class UN_EZ_API AWindElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWindElementAbility2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void setupAttack(ATori* newOwner, AWindElement* myElementIn, float lifeSpan, float damageIn, float innerRadiusIn, float outerRadiusIn);
	float currBuffDur;
	float damage;
	float outerRadius;
	float innerRadius;
	float pushForce = 2.0f;
	float currentTime;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		class AWindElement* myElement;
	UPROPERTY(BlueprintReadWrite)
		class ATori* enemyReference;
	UPROPERTY(EditAnywhere)
		float RadiusToEnemy;
	UPROPERTY(EditAnywhere)
		FVector pushDirection;

	TArray <AActor*> enemy;
	int numOfEnemy;
	FVector playerLocation;
	FVector enemyLocation;

	void checkForEnemy();


	USphereComponent* collider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
