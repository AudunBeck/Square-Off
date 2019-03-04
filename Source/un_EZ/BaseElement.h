// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "BaseElement.generated.h"

class ATori;

UCLASS()
class UN_EZ_API ABaseElement : public AActor
{
	GENERATED_BODY()

public:
	ABaseElement();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	int elementType = 0;

	bool isActive;

	void setPlayer(class ATori* newOwner);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class ATori* myOwner;
	ATori* getMyOwner();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Abilities")
		bool channelingAbility1 = false;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Abilities")
		bool channelingAbility2 = false;

	// Ability 1 variables.
	UFUNCTION(BlueprintCallable)
		virtual void ability1();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void ability1Anim();
	UFUNCTION(BlueprintCallable)
		virtual void ability1FireCode();
	UFUNCTION(BlueprintCallable)
		virtual void ability1End();
	UFUNCTION(BlueprintCallable)
		virtual int returnElementType();


	UPROPERTY(EditAnywhere, Category = "Ability1")
		float maxCooldownAbility1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float cooldownAbility1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		int maxAmmo1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		int ammoPerCd1;
	UPROPERTY(EditAnywhere, Category = "Ability1")
		int ammo1;


	// Ability 2 variables.
	UFUNCTION(BlueprintCallable)
		virtual void ability2();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void ability2Anim();
	UFUNCTION(BlueprintCallable)
		virtual void ability2FireCode();
	UFUNCTION(BlueprintCallable)
		virtual void ability2End();

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float maxCooldownAbility2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float cooldownAbility2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int maxAmmo2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int ammoPerCd2;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int ammo2;

	int switchToElement();

	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	//	void ability1AnimStart();
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	//	void ability1AnimEnd();

	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	//	void ability2AnimStart();
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	//	void ability2AnimEnd();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void resetAbility1();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
		void resetAbility2();

	
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		float attackSpeed = 1.f;
};
