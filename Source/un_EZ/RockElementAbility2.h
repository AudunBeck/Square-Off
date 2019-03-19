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
	ARockElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float movingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxMovingTime = 1.f;

	UPROPERTY(EditAnywhere)
		float speed = 500.f;
	float damageDivision; // here to easier fix dmg.

	UPROPERTY(EditAnywhere)
		float playerKnockback;

	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxHangTime = 0.3f;
	float hangTime;

	class ARockElement* myElement;

	FVector punchPos;
	FVector wallPos;

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxCollider;

	UPROPERTY(BlueprintReadWrite)
		bool isTouchingGround;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void moveWall(FRotator playerRot, float punchSpeed);

};
