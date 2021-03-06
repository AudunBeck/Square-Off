#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "FireElement.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "FireElementAbility2.generated.h"

UCLASS()
class UN_EZ_API AFireElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	AFireElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	class AFireElement* myElement;

	UPROPERTY(EditAnywhere, Category = "Ability2")
		USphereComponent* collider;
	
	FVector NewLocation;
	FVector forward;
	float attackRange;
	float damage;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
