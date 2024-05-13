// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Unreal2DTarget : TargetRules
{
	//---------------------------------------------------------------------------------------------
	public Unreal2DTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		Unreal2DTarget.ApplySharedTargetSettings( this );

		ExtraModuleNames.AddRange( new string[] { "Unreal2D" } );
	}
	//---------------------------------------------------------------------------------------------

	//---------------------------------------------------------------------------------------------
	internal static void ApplySharedTargetSettings(TargetRules Target )
	{
		Target.DefaultBuildSettings = BuildSettingsVersion.V5;
		Target.IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

	}
	//---------------------------------------------------------------------------------------------

}
