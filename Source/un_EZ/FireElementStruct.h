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
		float Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Knockback;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LifeSpan;
};