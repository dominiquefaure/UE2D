// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "Sprites/UE2DSpriteSkin.h"

//------------------------------------------------------------------------------------------------
FUE2DSpriteSkinSlot* FUE2DSpriteSkin::GetSkinSlot( FString SlotName )
{
	int SlotCount	=	Slots.Num();
	for( int i = 0 ; i < SlotCount ; i++ )
	{
		if( Slots[ i ].ArmatureSlotName == SlotName )
		{
			return &Slots[ i ];
		}
	}

	return nullptr;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FUE2DSpriteSkinSlotAttachmentTextureAtlas* FUE2DSpriteSkinSlot::GetTextureAtlasAttachment( int32 AttachmentIndex )
{
	if( ( AttachmentIndex >= 0 ) && ( AttachmentIndex < TextureAtlasAttachments.Num() ) )
	{
		return &TextureAtlasAttachments[ AttachmentIndex ];
	}
	return nullptr;

}
//------------------------------------------------------------------------------------------------
