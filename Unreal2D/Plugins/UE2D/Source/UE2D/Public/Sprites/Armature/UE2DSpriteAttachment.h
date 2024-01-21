// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpriteAttachment.generated.h"




UCLASS( transient , NotBlueprintable )
class UE2D_API UUE2DSpriteAttachment : public UObject
{
	GENERATED_BODY()

	friend class UUE2DSpriteInstance;
protected:

	void Init( FUE2DAttachmentSlot* Slot , UUE2DSpriteArmatureBone* InBone , FUE2DSpriteSkinSlot* InSkinSlot );

	void Draw( FUE2DSpriteRenderCommandBuilder* Builder , UUE2DTextureAtlas* Atlas );

protected:

	// the Slot definition
	FUE2DAttachmentSlot* SourceSlot;

	// the Bone it's attached to
	UUE2DSpriteArmatureBone* Bone;

	// the skin for this slot
	FUE2DSpriteSkinSlot* SkinSlot;

	// current Frame index in the Skin
	int32					CurrentAttachmentFrame;
};