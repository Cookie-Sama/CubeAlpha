// Copyright Epic Games, Inc. All Rights Reserved.

#include "CubeAlphaGameMode.h"
#include "CubeAlphaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACubeAlphaGameMode::ACubeAlphaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
