// Fill out your copyright notice in the Description page of Project Settings.


#include "Sprites/UE2DSpriteInstance.h"

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
	Sprite			=	InSprite;

	ArmatureInstance	=	NewObject<UUE2DSpriteArmatureInstance>();
	ArmatureInstance->Init( Sprite->Armature.Get() );

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void UUE2DSpriteInstance::Draw( FUE2DSpriteRenderCommandBuilder* Builder , UUE2DTextureAtlas* Atlas )
{
	if( ArmatureInstance == nullptr )
	{
		return;
	}

	int Count	=	ArmatureInstance->GetBoneCount();

	for( int i = 0 ; i < Count ; i++ )
	{
		Builder->AddSprite( Atlas->GetFrameAt( i ) , FColor::White , ArmatureInstance->GetBoneGlobalTransform( i ) );
	}
}
//------------------------------------------------------------------------------------------------
