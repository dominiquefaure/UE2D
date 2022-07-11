// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlas.h"

//---------------------------------------------------------------------------------------------
UUE2DSpriteAtlasFrame* UUE2DSpriteAtlas::GetFrameAt( int32 Index )
{
	if( (Index >= 0 ) && (Index < Frames.Num() ) )
	{
		return Frames[ Index ];
	}

	// not found
	return nullptr;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
int32 UUE2DSpriteAtlas::GetFrameIndex( UUE2DSpriteAtlasFrame* InFrame )
{
	for( int i = 0; i < Frames.Num(); i++ )
	{
		if( Frames[ i ] == InFrame )
		{
			return i;
		}
	}

	// not found
	return -1;
}
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
void UUE2DSpriteAtlas::AddFrame( FString Name , int TextureIndex , int SrcX , int SrcY , int Width , int Height , bool InRotate )
{
	// Add the Frame
	UUE2DSpriteAtlasFrame* Frame	=	NewObject<UUE2DSpriteAtlasFrame>( this );

	Frame->Name		=	Name;
	Frame->Texture	=	Textures[ TextureIndex ];
	Frame->X		=	SrcX;
	Frame->Y		=	SrcY;
	Frame->Width	=	Width;
	Frame->Height	=	Height;
	Frame->Rotated	=	InRotate;

	Frames.Add( Frame );
}
//---------------------------------------------------------------------------------------------
