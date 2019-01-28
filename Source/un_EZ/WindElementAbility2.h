// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility2.generated.h"

class AWindElement;

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
	void setupAttack(ATori* newOwner, AWindElement* myElementIn, float lifeSpan, float dashDistIn, float ccDurIn, float slowIn, float damageIn);
	float currBuffDur;
	float dashDist;
	float ccDur;
	float slow;
	float damage;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		class AWindElement* myElement;

	USphereComponent* collider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
