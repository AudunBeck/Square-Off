// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindElementAbility1.h"
#include "WindElementAbility2.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "WindElement.generated.h"

UCLASS()
class UN_EZ_API AWindElement : public ABaseElement
{
	GENERATED_BODY()

public:
	AWindElement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void ability1()override;
	virtual void ability1FireCode()override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability1")
		int combo = 0;

	virtual void ability2()override;
	virtual void ability2FireCode()override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ability2PullAnim();
	bool windUsingAbility2 = false;
	UFUNCTION(BlueprintImplementableEvent)
		void ability2PullParticle();

	virtual int returnElementType()override;

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility1> WindElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility2> WindElementAbility2_BP;

	// Ability 1
		///Value not used
	/*UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2lifeSpan = 2.5f;*/

		// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Damage = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float channelSpeed = 2000.f;

	UPROPERTY(BlueprintReadWrite, Category = "Ability1")
		float maxChannelTime;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxInterval = 0.4f;
	UPROPERTY(BlueprintReadWrite, Category = "Ability1")
		bool ability1Down;

	float interval;
	UPROPERTY(VisibleAnywhere, Category = "Ability1")
		float ability1BuffedDamage;
	float channelTime;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1KnockBack = 300.f;

	// Ability 2 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability2")
		float ability2Lifespan = 2.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float bonusSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2KnockBack = 300.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage = 15.f;
	UDataTable* BalancingTable;
};
