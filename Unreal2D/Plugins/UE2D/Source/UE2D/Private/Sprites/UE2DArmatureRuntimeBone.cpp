// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/UE2DArmatureRuntimeBone.h"

//------------------------------------------------------------------------------------------------
FUE2DArmatureRuntimeBone::FUE2DArmatureRuntimeBone()
{

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FUE2DArmatureRuntimeBone::~FUE2DArmatureRuntimeBone()
{

}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
void FUE2DArmatureRuntimeBone::AddChild( FUE2DArmatureRuntimeBone* Child )
{
	ChildBones.Add( Child );

	Child->ParentBone										=	this;
}
//------------------------------------------------------------------------------------------------
