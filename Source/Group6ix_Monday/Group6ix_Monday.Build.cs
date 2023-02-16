// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Group6ix_Monday : ModuleRules
{
	public Group6ix_Monday(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
