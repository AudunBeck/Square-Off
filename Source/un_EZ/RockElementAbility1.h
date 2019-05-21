#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "RockElement.h"
#include "Tori.h"
#include "RockElementAbility1.generated.h"

UCLASS()
class UN_EZ_API ARockElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	ARockElementAbility1();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	float attackRange;
	float chargedHit;
	float damage;
	float knockback;
	FVector NewLocation;
	FVector forward;
	FVector ownerPos;
	USphereComponent* collider;

	UPROPERTY(EditAnywhere)
		class ARockElement* myElement;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
