// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

UENUM(BlueprintType)
enum class CA_DamageType : uint8
{
	Physical UMETA(displayName = "Physical"),
	Magical UMETA(displayName = "Magical")
};

UENUM(BlueprintType)
enum class CA_AbilityID : uint8
{
	None UMETA(DisplayName = "None"),
	Primary UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary"),
	Active1 UMETA(DisplayName = "Active1"),
	Active2 UMETA(DisplayName = "Active2"),
	Active3 UMETA(DisplayName = "Active3"),
	Ultimate UMETA(DisplayName = "Ultimate")
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

    // Constructeur par defaut
    FCA_StatsRow()
        : Level(0)
        , Vitality(0.0f)
        , Strength(0.0f)
        , Intelligence(0.0f)
        , Agility(0.0f)
		, Endurance(0.0f)
    {}
};