// Copyright 2016-2020 TriAxis Games L.L.C. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class UE2DEditor : ModuleRules
{
    public UE2DEditor(ReadOnlyTargetRules rules) : base(rules)
    {

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				// ... add other public dependencies that you statically link with here ...
                
            }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                // ... add private dependencies that you statically link with here ...	
                "Engine",
                "Slate",
                "SlateCore",
                "RenderCore",
                "RHI",
                "NavigationSystem",
                "UnrealEd",
                "LevelEditor",
                "PropertyEditor",
                "RawMesh",
                "AssetTools",
                "AssetRegistry",
                "Projects",
                "EditorStyle",
                "InputCore",
                "DesktopPlatform",

                "UE2D",
            }
            );

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "Settings",
                "AssetTools",
                "LevelEditor"
            });

    }
}