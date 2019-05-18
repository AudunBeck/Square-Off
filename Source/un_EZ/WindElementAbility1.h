#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "WindElement.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility1.generated.h"

class AWindElement;
class ATori;

UCLASS()
class UN_EZ_API AWindElementAbility1 : public ABaseAbility
{
	GENERATED_BODY()

public:
	AWindElementAbility1();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	float currentTime;
	float myDistance;
	float myChannelSpeed;
	float distTraveled;
	float damage;
	float knockback;
	float ccDur;
	float slow;
	int numOfEnemy;
	TArray <AActor*> enemy;
	FVector playerLocation;
	FVector enemyLocation;
	FVector enemyForward;
	FVector a;
	FVector b;
	FVector spawnLocation;
	USphereComponent* collider;

	UPROPERTY(BlueprintReadWrite)
		class AWindElement* myElement;

	UPROPERTY(BlueprintReadWrite)
		class ATori* enemyReference;

	UPROPERTY(BlueprintReadWrite)
		float distToEnemy;

	UPROPERTY(BlueprintReadWrite)
		float dotValue;

	UPROPERTY(BlueprintReadWrite)
		float dotProduct;

	UPROPERTY(BlueprintReadWrite)
		float RadiusToEnemy;

	UPROPERTY(BlueprintReadWrite)
		FVector pushDirection;

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
