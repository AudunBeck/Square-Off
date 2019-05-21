#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "WindElement.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WindElementAbility2.generated.h"

class AWindElement;
class ATori;

UCLASS()
class UN_EZ_API AWindElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()

public:
	AWindElementAbility2();
	~AWindElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void checkForEnemies();

	FVector enemyLocation;
	FVector tempLocation;
	TArray<AActor*> foundEnemy;
	int numberOfEnemyFound;
	float radiusToEnemy;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WindElement collision")
		void stopCollision();

	UFUNCTION(BlueprintCallable, Category = "WindElement collision")
		void startCollision();

	UPROPERTY(BlueprintReadWrite)
		class AWindElement* myElement;

	UPROPERTY(BlueprintReadWrite)
		class ATori* enemyReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float radius = 350.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float knockback;
};
