#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GameFramework/Actor.h"
#include "Tori.h"
#include "RockElementAbility1.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "RockElementAbility2.generated.h"

UCLASS()
class UN_EZ_API ARockElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()

public:
	ARockElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void moveWall(FRotator playerRot, float punchSpeed);

	float damage;
	FVector punchPos;
	FVector wallPos;
	class ARockElement* myElement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxHangTime = 0.3f;
	float hangTime;

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxCollider;

	UPROPERTY(BlueprintReadWrite)
		bool isTouchingGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float movingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxMovingTime = 1.f;

	UPROPERTY(EditAnywhere)
		float speed = 500.f;
	float damageDivision;

	UPROPERTY(EditAnywhere)
		float playerKnockback;

	UPROPERTY(VisibleAnywhere, Category = "Hitplayer")
		ATori* hitPlayer = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
		void StartDestroy();

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UFUNCTION()
		void EndOnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
			UFUNCTION(BlueprintImplementableEvent)
				void moveAnim();

			UFUNCTION(BlueprintImplementableEvent)
				void StartDespawn();

			float lifespan;
			bool startedDestroy = false;
};
