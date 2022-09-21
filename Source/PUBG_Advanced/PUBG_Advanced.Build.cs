// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PUBG_Advanced : ModuleRules
{
	public PUBG_Advanced(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PublicIncludePaths.AddRange(new string[] { 
		"PUBG_Advanced/Public/GameMode",
        "PUBG_Advanced/Public/PlayerController",
        "PUBG_Advanced/Public/GameState",
        "PUBG_Advanced/Public/UI",
        "PUBG_Advanced/Public/PlayerState",
        "PUBG_Advanced/Public/Player",
        "PUBG_Advanced/Public/Animation",
        "PUBG_Advanced/Public/Animation/Notifies",
        "PUBG_Advanced/Public/Animation/Items",
        });
	
	}
}
