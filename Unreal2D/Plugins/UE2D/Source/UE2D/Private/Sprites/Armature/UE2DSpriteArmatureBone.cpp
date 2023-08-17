// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/Armature/UE2DSpriteArmatureBone.h"


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
