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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float BuffedDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float MaxCooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		int AmmoPerCD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float MoveRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		float LifeSpan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		int FireChi;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
		FVector BuffedScale;


};