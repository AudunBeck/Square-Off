#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "pickUp.h"
#include "pickUpSpawner.generated.h"

UCLASS()
class UN_EZ_API ApickUpSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ApickUpSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "PickUps")
		TSubclassOf<class ApickUp> ElementToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "PickUps")
		ApickUp* SpawnedElement;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "PickUps")
		float timeBetweenPickUps;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "PickUps")
		void elementPickedUp();

	UFUNCTION(BlueprintCallable, Category = "PickUps")
		void spawnElement();
};
