// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/Armature/UE2DSpriteArmature.h"


//------------------------------------------------------------------------------------------------
const FUE2DArmatureBone* UUE2DSpriteArmature::GetRoot()const
{
	return &Bones[ 0 ];
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteArmature::GetChildBones( uint32 BoneIndex , TArray<FUE2DArmatureBone*> ChildList )
{
	int t_BoneCount	=	Bones.Num();

	for( int i = 0 ; i < t_BoneCount ; i ++ )
	{
		if( Bones[ i ].ParentBone == BoneIndex )
		{
			ChildList.Add( &Bones[ i ] );
		}
	}
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
TArray<FUE2DArmatureBone*> UUE2DSpriteArmature::GetChildBones( uint32 BoneIndex )
{
	TArray<FUE2DArmatureBone*> ChildList;

	GetChildBones( BoneIndex , ChildList );

	return ChildList;
}
//------------------------------------------------------------------------------------------------

