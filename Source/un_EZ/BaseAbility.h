// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tori.h"
#include "BaseElement.h"
#include "GameFramework/Actor.h"
#include "BaseAbility.generated.h"

UCLASS()
class UN_EZ_API ABaseAbility : public AActor
{
	GENERATED_BODY()

public:
	ABaseAbility();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual ATori* getMyOwner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATori* myPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
		UParticleSystem* hitVFX;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "VFX")
		void hitEnemyVFX(FVector enemyLocation);

	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly)
				FVector direction;
	
	UPROPERTY(BlueprintReadOnly)
		bool hasHit = false;
};
