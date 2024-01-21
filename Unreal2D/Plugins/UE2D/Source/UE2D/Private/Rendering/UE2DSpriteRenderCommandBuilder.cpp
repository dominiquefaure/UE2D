// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "Rendering/UE2DSpriteRenderCommandBuilder.h"

const float DeltaYCoef	=	0.1f;

//------------------------------------------------------------------------------
FUE2DSpriteRenderCommandBuilder::FUE2DSpriteRenderCommandBuilder()
{

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
FUE2DSpriteRenderCommandBuilder::~FUE2DSpriteRenderCommandBuilder()
{

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
const TArray<FUE2DSpriteRenderCommand>& FUE2DSpriteRenderCommandBuilder::GetCommands()const
{
	return Commands;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void FUE2DSpriteRenderCommandBuilder::Begin()
{
	Commands.Empty();
	CommandCount						=	0;
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void FUE2DSpriteRenderCommandBuilder::Finish()
{
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void FUE2DSpriteRenderCommandBuilder::AddSprite( UUE2DTextureAtlasFrame* InFrame , FColor InColor , FTransform InTransform )
{
	if( InFrame != nullptr )
	{
		FUE2DSpriteRenderCommand Command;

		Command.Set( InFrame , InTransform , InColor , InFrame->Texture , CommandCount * DeltaYCoef );

		Commands.Add( Command );
		CommandCount ++;
	}
}
//------------------------------------------------------------------------------

