// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Unreal2DEditorTarget : TargetRules
{
	public Unreal2DEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
	
		if(!bBuildAllModules)
		{
			NativePointerMemberBehaviorOverride = PointerMemberBehavior.Disallow;
		}

		Unreal2DTarget.ApplySharedTargetSettings( this );

		ExtraModuleNames.AddRange( new string[] { "Unreal2D" } );


	}
}
