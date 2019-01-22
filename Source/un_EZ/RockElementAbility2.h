// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tori.h"
#include "RockElementAbility1.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "RockElementAbility2.generated.h"

UCLASS()
class UN_EZ_API ARockElementAbility2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockElementAbility2();
	
	UPROPERTY(EditAnywhere)
		UBoxComponent* boxCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Owner of the attack
	void setupAttack(ATori * newOwner, FVector scale, float lifeSpan);

	UPROPERTY(EditAnywhere)
		bool moving = false;

	UPROPERTY(EditAnywhere)
		bool shouldMove = false;

	UPROPERTY(EditAnywhere)
		float speed = 300.f;

	FVector punchPos;
	FVector wallPos;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		class ATori* myOwner;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void moveWall(FVector playerLoc);

};
