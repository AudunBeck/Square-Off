// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FireElementStruct.generated.h"

USTRUCT(BlueprintType)
struct FFireElementStruct : public FTableRowBase
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BuffedDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoPerCD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeSpan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int FireChi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector BuffedScale;


};