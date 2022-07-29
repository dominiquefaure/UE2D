// Copyright 2016-2020 TriAxis Games L.L.C. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class UE2DSpineImporter : ModuleRules
{
    public UE2DSpineImporter(ReadOnlyTargetRules rules) : base(rules)
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
                "UnrealEd",
 				"EditorFramework",

                "UE2D",
                "UE2DEditor"
            }
            );

        PrivateIncludePathModuleNames.AddRange(
            new string[] {
                "Settings",
                "AssetTools",
 				"AssetRegistry",
            });

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"AssetRegistry"
			});

    }
}