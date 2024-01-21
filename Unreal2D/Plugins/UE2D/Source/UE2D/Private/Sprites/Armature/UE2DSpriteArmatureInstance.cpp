// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "Sprites/Armature/UE2DSpriteArmatureInstance.h"
#include "Sprites/Armature/UE2DSpriteArmature.h"
#include "Sprites/Armature/UE2DSpriteArmatureBone.h"


//------------------------------------------------------------------------------------------------
UUE2DSpriteArmatureInstance::UUE2DSpriteArmatureInstance()
{

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
UUE2DSpriteArmatureInstance::~UUE2DSpriteArmatureInstance( )
{
	Bones.Empty();
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteArmatureInstance::Init( UUE2DSpriteArmature* InArmature )
{
	Bones.Empty();

	Armature	=	InArmature;

	// Create all the necessary Bones
	for( int i = 0 ; i < Armature->Bones.Num(); i ++ )
	{
		UUE2DSpriteArmatureBone* Bone	=	NewObject< UUE2DSpriteArmatureBone>();
		Bones.Add( Bone );
	}

	UUE2DSpriteArmatureBone* RuntimeBone;
	FUE2DArmatureBone* SourceBone;
	for( int i = 0 ; i < Armature->Bones.Num(); i ++ )
	{
		SourceBone						=	&(Armature->Bones[ i ]);
		RuntimeBone						=	Bones[ i ];

		RuntimeBone->LocalTransform		=	SourceBone->DefaultTransform;

		if( SourceBone->ParentBone != -1 )
		{
			Bones[ SourceBone->ParentBone ]->AddChild( RuntimeBone );
		}
	}

	// compute all the Global transforms
	Bones[ 0 ]->ComputeGlobalTransform();
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
int UUE2DSpriteArmatureInstance::GetBoneCount()const
{
	return Bones.Num();
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
UUE2DSpriteArmatureBone* UUE2DSpriteArmatureInstance::GetBone( int32 Index )
{

	if( ( Index >= 0 ) && ( Index < Bones.Num() ) )
	{
		return Bones[ Index ];
	}

	return nullptr;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FTransform UUE2DSpriteArmatureInstance::GetBoneGlobalTransform( int32 Index )
{
	if( ( Index >= 0 ) && ( Index < Bones.Num() ) )
	{
		return Bones[ Index ]->GlobalTransform;
	}

	return FTransform::Identity;
}
//------------------------------------------------------------------------------------------------
