// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/*
struct FUE2DRuntimeArmatureBone
{
	// the bone in the ArmatureDefinition
	FUE2DArmatureBone* SourceBone;

	// pointer to the Parent Bone
	FUE2DRuntimeArmatureBone* ParentBone;

	// Local Transform Applyed to this bone
	FTransform LocalTransform;

	// Global Tranform compared to SpriteOrigin
	FTransform GlobalTransform;

	// pointer to the Child bones
	TArray<FUE2DRuntimeArmatureBone*> ChildBones;
};
*/

/*
* Instance of a UUE2DSprite.
*/
class UE2D_API FUE2DArmatureRuntimeBone
{
public:
	FUE2DArmatureRuntimeBone();
	~FUE2DArmatureRuntimeBone();

//	void Initialize( FUE2DArmatureBone* InSourceBone );


	void AddChild( FUE2DArmatureRuntimeBone* Child );

//private:

	// the bone in the ArmatureDefinition
	FUE2DArmatureBone* SourceBone;

	// pointer to the Parent Bone
	FUE2DArmatureRuntimeBone* ParentBone;

	// Local Transform Applyed to this bone
	FTransform LocalTransform;

	// Global Tranform compared to SpriteOrigin
	FTransform GlobalTransform;

	// pointer to the Child bones
	TArray<FUE2DArmatureRuntimeBone*> ChildBones;


};