// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "UE2DSpriteSkin.generated.h"

class UUE2DTextureAtlas;


USTRUCT()
struct FUE2DSpriteSkinSlotAttachmentTextureAtlas
{
	GENERATED_USTRUCT_BODY()

	// Index of the TextureAtlas used for this Attachment
	UPROPERTY( EditAnywhere )
	uint32 		AtlasIndex;

	// the Texture Atlas
	UPROPERTY( EditAnywhere )
	UUE2DTextureAtlas* TextureAtlas;

	// the Frame in the Atlas used
	UPROPERTY( EditAnywhere )
	uint32		Frame;

	// Transform to apply in order to place the Frame at the right position related to the Bone it attached to
	UPROPERTY( EditAnywhere )
		FTransform	PivotTransform;

};

USTRUCT()
struct FUE2DSpriteSkinSlot
{
	GENERATED_USTRUCT_BODY()

	// name of the Armature Slot this skin represent
	UPROPERTY( EditAnywhere )
	FString				ArmatureSlotName;

	// list of Texture Atlas attachment used if the Slot is a Texture Atlas Slot
	UPROPERTY( EditAnywhere )
	TArray< FUE2DSpriteSkinSlotAttachmentTextureAtlas> TextureAtlasAttachments;

	// gethte Attachment at the given index for this Skin slot
	FUE2DSpriteSkinSlotAttachmentTextureAtlas* GetTextureAtlasAttachment( int32 AttachmentIndex );
};

USTRUCT()
struct FUE2DSpriteSkin
{
	GENERATED_USTRUCT_BODY()

	// list the different TExture Atlas that can be used by the skin
	UPROPERTY( EditAnywhere )
	TArray< UUE2DTextureAtlas*> TextureAtlases;

	// the different Slots that allow to customize the Sprite appearance
	UPROPERTY( EditAnywhere )
	TArray< FUE2DSpriteSkinSlot> Slots;

	FUE2DSpriteSkinSlot* GetSkinSlot( FString SlotName );

};