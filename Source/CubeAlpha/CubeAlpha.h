// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class CA_DamageType : uint8
{
	Physical UMETA(displayName = "Physical"),
	Magical UMETA(displayName = "Magical")
};