#pragma once

#include "CoreMinimal.h"
#include "FireElementAbility1.h"
#include "FireElementAbility2.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "FireElement.generated.h"


UCLASS()
class UN_EZ_API AFireElement : public ABaseElement
{
	GENERATED_BODY()

public:

	AFireElement();

	virtual void ability1()override;
	virtual void ability1FireCode()override;
	virtual void ability1End()override;
	virtual void ability2()override;
	virtual void ability2FireCode()override;
	virtual void ability2End()override;
	virtual int returnElementType()override;
	void BeginPlay()override;

	UFUNCTION(BlueprintImplementableEvent)
		void ability1HitAnim();

	UFUNCTION(BlueprintImplementableEvent)
		void ability2HitAnim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Particles")
		void attachFireEmitters();

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AFireElementAbility1> FireElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AFireElementAbility2> FireElementAbility2_BP;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1lifeSpan = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float launchSpeed_1 = 300.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Damage;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Knockback;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1BuffedDamage;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1BuffedKnockback;

	bool abilityHit = false;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Range;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		int ammo1Refill = 2;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Lifespan = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float launchSpeed_2 = 2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability2")
		int maxFireChi = 2;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animations")
		int fireChi;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		FVector boostedAbility1Scale;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage;
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Knockback;

	UDataTable* BalancingTable;
};
