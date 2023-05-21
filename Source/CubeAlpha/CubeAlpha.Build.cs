// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CubeAlpha : ModuleRules
{
	public CubeAlpha(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(new string[]
		{"CubeAlpha", 
            "CubeAlpha/Character",
            "CubeAlpha/Character/Familiar",
            "CubeAlpha/Character/Monster",
            "CubeAlpha/Character/Mount",
            "CubeAlpha/Character/NPC",
            "CubeAlpha/Character/Player",
            "CubeAlpha/System",
            "CubeAlpha/System/GAS",
            "CubeAlpha/System/GAS/NPC",
            "CubeAlpha/System/GAS/Player",
            "CubeAlpha/System/GAS/AttributeSets",
            "CubeAlpha/System/IA",
            "CubeAlpha/System/Player",
            "CubeAlpha/World",
            "CubeAlpha/World/Landscape",
            "CubeAlpha/World/POI",
            "CubeAlpha/World/Town"
        });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
	}
}
