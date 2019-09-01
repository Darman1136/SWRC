// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SWRCEditor : ModuleRules
{
	public SWRCEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "FPS" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "Engine", "Core", "GameplayTasks" });
	}
}
