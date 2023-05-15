// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CubeAlpha : ModuleRules
{
	public CubeAlpha(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}