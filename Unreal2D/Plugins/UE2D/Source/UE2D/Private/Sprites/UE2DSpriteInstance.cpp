// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/UE2DSpriteInstance.h"
#include "Sprites/Armature/UE2DSpriteAttachment.h"
#include "Sprites/Armature/UE2DSpriteArmatureBone.h"

//------------------------------------------------------------------------------------------------
UUE2DSpriteInstance::UUE2DSpriteInstance( )
{
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
UUE2DSpriteInstance::~UUE2DSpriteInstance()
{
}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::SetSprite( UUE2DSprite* InSprite )
{
	Sprite				=	InSprite;

	GenerateBones( Sprite->Armature.Get() );
	GenerateAttachments( Sprite->Armature.Get() );
}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
int UUE2DSpriteInstance::GetBoneCount()const
{
	return Bones.Num();
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
UUE2DSpriteArmatureBone* UUE2DSpriteInstance::GetBone( int32 Index )
{
	if( ( Index >= 0 ) && ( Index < Bones.Num() ) )
	{
		return Bones[ Index ];
	}

	return nullptr;
}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::GenerateBones( UUE2DSpriteArmature* Armature )
{
	// Create all the necessary Bones
	for( int i = 0 ; i < Armature->Bones.Num(); i ++ )
	{
		UUE2DSpriteArmatureBone* Bone	=	NewObject< UUE2DSpriteArmatureBone>();
		Bones.Add( Bone );
	}

	UUE2DSpriteArmatureBone* RuntimeBone;
	FUE2DArmatureBone* SourceBone;
	for( int i = 0 ; i < Armature->Bones.Num(); i ++ )
	{
		SourceBone						=	&( Armature->Bones[ i ] );
		RuntimeBone						=	Bones[ i ];

		RuntimeBone->LocalTransform		=	SourceBone->DefaultTransform;

		if( SourceBone->ParentBone != -1 )
		{
			Bones[ SourceBone->ParentBone ]->AddChild( RuntimeBone );
		}
	}

	// compute all the Global transforms
	Bones[ 0 ]->ComputeGlobalTransform();

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::GenerateAttachments( UUE2DSpriteArmature* Armature )
{
	// Get the number of Slots defined in the Armature
	int AttachmentCount	=	Armature->Slots.Num();

	for( int i = 0 ; i < AttachmentCount ; i ++ )
	{
		GenerateAttachment( Armature->Slots[ i ] );

	}
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::GenerateAttachment( FUE2DAttachmentSlot& Slot )
{
	// Create new Attachment
	UUE2DSpriteAttachment* NewAttachment;
	NewAttachment					=	NewObject< UUE2DSpriteAttachment>();
/*
	if( Slot.AttachmentType == EAttachmentSlotType::TextureAtlas )
	{
		NewAttachment					=	NewObject< UUE2DSpriteAttachmentTextureAtlas>();
	}
	else
	{
	}
*/
	Attachments.Add( NewAttachment );

	NewAttachment->Init( &Slot , GetBone( Slot.BoneIndex ) , Sprite->GetSkinSlot( Slot.Name ) );
	
	FUE2DSpriteSkinSlot* SkinSlot			=	Sprite->GetSkinSlot( Slot.Name );
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::Draw( FUE2DSpriteRenderCommandBuilder* Builder , UUE2DTextureAtlas* Atlas )
{
	int Count	=	Attachments.Num();

	for( int i = 0 ; i < Count ; i++ )
	{
		Attachments[ i ]->Draw( Builder , Atlas );
	}
}
//------------------------------------------------------------------------------------------------
