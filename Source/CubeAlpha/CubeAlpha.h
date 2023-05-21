// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

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

UENUM(BlueprintType)
enum class ERarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary
};
