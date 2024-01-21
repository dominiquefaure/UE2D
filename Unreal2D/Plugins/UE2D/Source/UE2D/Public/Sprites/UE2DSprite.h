// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Sprites/Armature/UE2DSpriteArmature.h"

#include "UE2DSpriteSkin.h"

#include "UE2DSprite.generated.h"

// represent a Bone in the Armature of a Sprite
USTRUCT()
struct FUE2DSpriteBone
{
	GENERATED_USTRUCT_BODY()

		// name o the Bone, unique in the Armature
		UPROPERTY( EditAnywhere )
		FString Name;

	// Index of the Parent bone
	UPROPERTY( EditAnywhere )
		int32 ParentBone;

	// Bone Default transform
	UPROPERTY( EditAnywhere )
		FTransform DefaultTransform;
};



UENUM()
enum class EUE2DSpriteAttachmentSlotType : uint8
{
	TextureAtlas ,
	SubSprite
};


USTRUCT()
struct FUE2DSpriteAttachmentBase
{
	GENERATED_USTRUCT_BODY()

	// unique name of the Attachment
	UPROPERTY( EditAnywhere )
	FString Name;

	// the Bone this Slot is linked to
	UPROPERTY( EditAnywhere )
	int32 BoneIndex;

	UPROPERTY( EditAnywhere )
	EAttachmentSlotType AttachmentType;
};

USTRUCT()
struct FUE2DSpriteAttachmentTextureAtlasSlot
{
	GENERATED_USTRUCT_BODY()

	// the Frame in the Atlas used
	UPROPERTY( EditAnywhere )
	uint32		Frame;

	// Transform to apply in order to place the Frame at the right position related to the Bone it attached to
	UPROPERTY( EditAnywhere )
	FTransform	PivotTransform;

};

USTRUCT()
struct FUE2DSpriteAttachmentTextureAtlas : public FUE2DSpriteAttachmentBase
{
	GENERATED_USTRUCT_BODY()

	// the TExture atlas that store all the frames that can be used for this Attachment
	UPROPERTY( EditAnywhere )
	TObjectPtr<UUE2DTextureAtlas> TextureAtlas;

	// the different Slots of this attachment
	UPROPERTY( EditAnywhere )
	TArray< FUE2DSpriteAttachmentTextureAtlasSlot> Slots;

	UPROPERTY( EditAnywhere )
	int DefaultSlot;
};


/**
 * 
 */
UCLASS( hidecategories=Object , BlueprintType , meta = ( DisplayThumbnail = "true" ) )
class UE2D_API UUE2DSprite : public UDataAsset
{
	GENERATED_BODY()
public:

	// the Bones that compose the Armature of the Sprite
	UPROPERTY( EditAnywhere )
	TArray<FUE2DSpriteBone> Bones;

	UPROPERTY( EditAnywhere )
	TArray< FUE2DSpriteAttachmentTextureAtlas> TextureAtlasSlots;

/*	UPROPERTY(EditAnywhere)
	TObjectPtr<UUE2DSpriteArmature> Armature;

	UPROPERTY( EditAnywhere )
	FUE2DSpriteSkin					Skin;


	FUE2DSpriteSkinSlot* GetSkinSlot( FString SlotName );
*/
};
