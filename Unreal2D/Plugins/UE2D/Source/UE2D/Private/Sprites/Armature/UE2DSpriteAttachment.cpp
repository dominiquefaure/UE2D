// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/Armature/UE2DSpriteAttachment.h"

#include "Sprites/Armature/UE2DSpriteArmature.h"

//------------------------------------------------------------------------------------------------
void UUE2DSpriteAttachment::Init( FUE2DAttachmentSlot* Slot , UUE2DSpriteArmatureBone* InBone , FUE2DSpriteSkinSlot* InSkinSlot )
{
	SourceSlot				=	Slot;
	Bone					=	InBone;
	SkinSlot				=	InSkinSlot;

	CurrentAttachmentFrame	=	SourceSlot->DefaultAttachmentIndex;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteAttachment::Draw( FUE2DSpriteRenderCommandBuilder* Builder , UUE2DTextureAtlas* Atlas )
{
	if( Bone == nullptr )
	{
		return;
	}
	if( SkinSlot == nullptr )
	{
		return;
	}

	if( CurrentAttachmentFrame >= 0 )
	{
		FUE2DSpriteSkinSlotAttachmentTextureAtlas* Attachment	=	SkinSlot->GetTextureAtlasAttachment( CurrentAttachmentFrame );
		
		if( Attachment != nullptr )
		{
			Builder->AddSprite( Attachment->TextureAtlas->GetFrameAt( Attachment->Frame ) , FColor::White , Bone->GetGlobalTransform() );

		}
	}

}
//------------------------------------------------------------------------------------------------
