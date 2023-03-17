// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DSprite.h"
#include "UE2DSpriteInstance.generated.h"


class FUE2DArmatureRuntimeBone;
class FUE2DArmatureRuntimeAttachmentBase;


/*
* Instance of a UUE2DSprite.
*/
UCLASS()
class UE2D_API UUE2DSpriteInstance : public UObject
{
	GENERATED_BODY()

public:

	//void PlayAnimation( const FString& Animation Name );

	// Initialize the Instance from a Sprite
	void Initialize( UUE2DSprite* InSprite );


private:

	// Create all the Runtime bones needed to represent the Armature hierarchy
	void InitializeBones( UUE2DSpriteArmature* Armature );


// Properties
private:

	// the Sprite that store all the data for this instance
	UUE2DSprite* Sprite;

	TArray<FUE2DArmatureRuntimeBone* > Bones;
//	FUE2DRuntimeArmatureBone* RootBone;
};