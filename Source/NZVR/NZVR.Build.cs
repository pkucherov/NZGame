// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NZVR : ModuleRules
{
	public NZVR(TargetInfo Target)
	{
        PublicIncludePaths.AddRange(new string[] {
            "NZVR/Vest"
        });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "NetworkReplayStreaming",
            "Json",
            "HeadMountedDisplay"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { "SlateCore", "Slate" });
        
        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd", "PropertyEditor" });
        }

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        // if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        // {
        //		if (UEBuildConfiguration.bCompileSteamOSS == true)
        //		{
        //			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //		}
        // }
    }
}
