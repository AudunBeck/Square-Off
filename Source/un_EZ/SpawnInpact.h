// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tori.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnInpact.generated.h"

UCLASS()
class UN_EZ_API ASpawnInpact : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnInpact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
		float damage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ATori* myPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UShapeComponent* collider;

	UFUNCTION()
		virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
