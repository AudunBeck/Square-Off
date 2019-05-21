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
	virtual void ability2()override;
	virtual void ability2FireCode()override;
	virtual int returnElementType()override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability1")
		int combo = 0;

	bool windUsingAbility2 = false;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void ability2PullAnim();

	UFUNCTION(BlueprintImplementableEvent)
		void ability2PullParticle();

	// Holds the pointers for element abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility1> WindElementAbility1_BP;

	UPROPERTY(EditAnywhere, Category = "Abilities")
		TSubclassOf<class AWindElementAbility2> WindElementAbility2_BP;

	// Ability 1
		// Damage properties
	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Damage = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "Ability1")
		float ability1BuffedDamage;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1Range = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float channelSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		float ability1KnockBack = 300.f;

	UPROPERTY(VisibleAnywhere, Category = "Ability1")
		float ability1BuffedKnockBack;

	UPROPERTY(BlueprintReadWrite, Category = "Ability1")
		bool ability1Down;

	// Ability 2 
	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Damage = 15.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Gravity;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2Radius;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float bonusSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		float ability2KnockBack = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability2")
		float ability2Lifespan = 2.f;

	UDataTable* BalancingTable;
};
