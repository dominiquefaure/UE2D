// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "Sprites/Armature/UE2DSpriteArmatureBone.h"

//------------------------------------------------------------------------------------------------
FTransform UUE2DSpriteArmatureBone::GetGlobalTransform()const
{
	return GlobalTransform;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteArmatureBone::ComputeGlobalTransform()
{

	if( Parent != nullptr )
	{
		GlobalTransform	=	Parent->GlobalTransform * LocalTransform;
	}
	else
	{
		GlobalTransform	=	LocalTransform;
	}

	// compute recursively the Global transform of it's childs
	int ChildCount		=	Childs.Num();
	for( int i = 0 ; i < ChildCount ; i ++ )
	{
		Childs[i]->ComputeGlobalTransform();

	}
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteArmatureBone::AddChild( UUE2DSpriteArmatureBone* Child )
{
	Child->Parent	=	this;
	Childs.Add( Child );
}
//------------------------------------------------------------------------------------------------
