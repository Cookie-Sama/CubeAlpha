#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "CubeAlphaStatsRow.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCubeAlphaStatsRow : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FCA_StatsRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Vitality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Intelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Agility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Endurance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ExperienceToNextLevel;

	FCA_StatsRow()
		: Level(0)
		, Vitality(0.0f)
		, Strength(0.0f)
		, Intelligence(0.0f)
		, Agility(0.0f)
		, Endurance(0.0f)
	    , ExperienceToNextLevel(0)
	{}
};