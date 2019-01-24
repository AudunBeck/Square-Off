// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "Tori.h"
#include "RockElementAbility1.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "RockElementAbility2.generated.h"

UCLASS()
class UN_EZ_API ARockElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockElementAbility2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Owner of the attack
	void setupAttack(ATori * newOwner, FVector scale, float lifeSpan, float wallSpeed);

	UPROPERTY(EditAnywhere)
		float movingTime;

	UPROPERTY(EditAnywhere)
		float maxMovingTime = 1.f;

	UPROPERTY(EditAnywhere)
		float speed = 500.f;

	FVector punchPos;
	FVector wallPos;

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxCollider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void moveWall(FVector playerLoc, float punchSpeed);

};
