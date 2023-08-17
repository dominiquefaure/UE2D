// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DSprite.h"
#include"Armature/UE2DSpriteArmatureInstance.h"
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
	UUE2DSpriteInstance();
	virtual ~UUE2DSpriteInstance();


	//void PlayAnimation( const FString& Animation Name );

	// Initialize the Instance from a Sprite
	void SetSprite( UUE2DSprite* InSprite );


	void Draw( FUE2DSpriteRenderCommandBuilder* Builder , UUE2DTextureAtlas* Atlas );

private:



// Properties
private:

	// the Sprite that store all the data for this instance
	UUE2DSprite* Sprite;

	UUE2DSpriteArmatureInstance* ArmatureInstance;
};