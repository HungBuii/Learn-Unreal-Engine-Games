// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RobotShooter : ModuleRules
{
	public RobotShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"RobotShooter",
			"RobotShooter/Variant_Platforming",
			"RobotShooter/Variant_Platforming/Animation",
			"RobotShooter/Variant_Combat",
			"RobotShooter/Variant_Combat/AI",
			"RobotShooter/Variant_Combat/Animation",
			"RobotShooter/Variant_Combat/Gameplay",
			"RobotShooter/Variant_Combat/Interfaces",
			"RobotShooter/Variant_Combat/UI",
			"RobotShooter/Variant_SideScrolling",
			"RobotShooter/Variant_SideScrolling/AI",
			"RobotShooter/Variant_SideScrolling/Gameplay",
			"RobotShooter/Variant_SideScrolling/Interfaces",
			"RobotShooter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
