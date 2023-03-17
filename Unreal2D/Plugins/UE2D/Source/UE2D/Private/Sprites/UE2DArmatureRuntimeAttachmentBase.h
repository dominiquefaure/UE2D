// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FUE2DArmatureRuntimeBone;

/*
* Instance of a UUE2DSprite.
*/
class UE2D_API FUE2DArmatureRuntimeAttachmentBase
{
public:
	FUE2DArmatureRuntimeAttachmentBase();
	~FUE2DArmatureRuntimeAttachmentBase();


private:

	// pointer to the Armature definition
	FUE2DArmatureAttachmentSlot* ArmatureSlot;

	// The runtime Bone this Attachment is linked to
	FUE2DArmatureRuntimeBone* RuntimeBone;
};