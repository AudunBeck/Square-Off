#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "WaterElement.h"
#include "GameFramework/Actor.h"
#include "WaterElementAbility2.generated.h"

class AWaterElement;

UCLASS()
class UN_EZ_API AWaterElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	AWaterElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	float currBuffDur;
	float ccDur;
	float slow;
	float damage;
	FVector NewLocation;

	UFUNCTION(BlueprintCallable, Category = "Output Log WaterAbility 2")
		void outputLog();

	UPROPERTY(EditAnywhere, Category = "Ability2", BlueprintReadWrite)
		class AWaterElement* myElement;

	UCapsuleComponent* collider;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
