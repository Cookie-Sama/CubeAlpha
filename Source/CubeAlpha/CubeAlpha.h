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

UENUM(BlueprintType)
enum class EEquipmentAttribute : uint8
{
	None UMETA(DisplayName = "None"),
	Defense UMETA(DisplayName = "Defense"),
	Vitality UMETA(DisplayName = "Vitality"),
	Strength UMETA(DisplayName = "Strength"),
	Intelligence UMETA(DisplayName = "Intelligence"),
	Agility UMETA(DisplayName = "Agility"),
	Endurance UMETA(DisplayName = "Endurance"),
	PhysicalDamage UMETA(DisplayName = "PhysicalDamage"),
	MagicalDamage UMETA(DisplayName = "MagicalDamage"),
	PhysicalResistance UMETA(DisplayName = "PhysicalResistance"),
	MagicalResistance UMETA(DisplayName = "MagicalResistance"),
};

UENUM(BlueprintType)
enum class EClassType : uint8
{
	Mage,
	Warrior,
	Archer,
	Summoner,
	All
};