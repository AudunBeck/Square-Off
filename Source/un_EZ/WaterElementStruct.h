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
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Knockback;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeSpan;
};