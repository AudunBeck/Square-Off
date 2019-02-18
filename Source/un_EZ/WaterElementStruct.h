// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WaterElementStruct.generated.h"

USTRUCT(BlueprintType)
struct FWaterElementStruct : public FTableRowBase
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageBuffed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxCharge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoPerCD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeSpan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Slow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SlowDur;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BoltSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SlowBuffed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SlowDurBuffed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BoltSpeedBuffed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CounterDash;

};