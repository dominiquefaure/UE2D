// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/UE2DSpriteInstance.h"

//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::Initialize( UUE2DSprite* InSprite )
{
	Sprite			=	InSprite;

	InitializeBones( Sprite->Armature.Get() );
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::InitializeBones( UUE2DSpriteArmature* Armature )
{
	// handle the edge case Armature is not set
	if( !Armature )
	{
		return;
	}
/*
	// Create the different Runtime Bones
	int BoneCount								=	Armature->Bones.Num();
	for( int i = 0 ; i < BoneCount ; i ++ )
	{
		FUE2DArmatureRuntimeBone* NewRuntimeBone	=	new FUE2DArmatureRuntimeBone();
		NewRuntimeBone->SourceBone					=	&(Armature->Bones[ i ]);
		Bones.Add( NewRuntimeBone );
	}

	// Build the Hierarchy Links
	FUE2DArmatureBone* TempSourceBone;
	FUE2DArmatureRuntimeBone* TempRuntimeBone;

	for( int i = 0 ; i < BoneCount ; i ++ )
	{
		TempRuntimeBone								=	Bones[ i ];
		TempSourceBone								=	Bones[ i ]->SourceBone;

		// if the Source bone have a Parent
		if( TempSourceBone->ParentBone != -1 )
		{
			Bones[ TempSourceBone->ParentBone ]->AddChild( TempRuntimeBone );
		}
	}
	*/
}
//------------------------------------------------------------------------------------------------

