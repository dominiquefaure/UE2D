// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

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


	int GetBoneCount()const;
	UUE2DSpriteArmatureBone* GetBone( int32 Index );


private:

	// generate the differne tbones used to animate the Sprite
	void GenerateBones( UUE2DSpriteArmature* Armature );

	void GenerateAttachments( UUE2DSpriteArmature* Armature );

	void GenerateAttachment( FUE2DAttachmentSlot& Slot );


// Properties
private:

	// the Sprite that store all the data for this instance
	UUE2DSprite* Sprite;

	//The different bones that compose the Sprite
	TArray<UUE2DSpriteArmatureBone*> Bones;


	// the different Attachments that draw this sprite
	TArray<UUE2DSpriteAttachment*> Attachments;
};