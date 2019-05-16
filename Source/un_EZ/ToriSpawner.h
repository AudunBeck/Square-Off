#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ToriSpawner.generated.h"

UCLASS()
class UN_EZ_API AToriSpawner : public ACharacter
{
	GENERATED_BODY()

public:
	AToriSpawner();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Player")
		float directionSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning Player")
		float spawnHeight = 900.f;

	UFUNCTION(BlueprintImplementableEvent)
		void spawnPlayer();

	FVector direction;
	float inAxis;
	void moveDirection(float AxisValue);

};
