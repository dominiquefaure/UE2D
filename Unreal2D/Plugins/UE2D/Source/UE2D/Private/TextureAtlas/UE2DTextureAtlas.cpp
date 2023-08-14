// Fill out your copyright notice in the Description page of Project Settings.


#include "TextureAtlas/UE2DTextureAtlas.h"

//---------------------------------------------------------------------------------------------
UUE2DTextureAtlasFrame* UUE2DTextureAtlas::GetFrameAt( int32 Index )
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
int32 UUE2DTextureAtlas::GetFrameIndex( UUE2DTextureAtlasFrame* InFrame )
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
void UUE2DTextureAtlas::AddFrame( UTexture2D* InTexture , FString Name , int SrcX , int SrcY , int Width , int Height , bool InRotated )
{
	int Index	=	-1;

	if( !Textures.Contains( InTexture ) )
	{
		Textures.Add( InTexture );
	}
	Textures.Find( InTexture , Index );
//	Index	=	Textures.IndexOf( InTexture );

	AddFrame( Name , Index , SrcX , SrcY , Width , Height , InRotated );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void UUE2DTextureAtlas::AddFrame( FString Name , int TextureIndex , int SrcX , int SrcY , int Width , int Height , bool InRotate )
{
	// Add the Frame
	UUE2DTextureAtlasFrame* Frame	=	NewObject<UUE2DTextureAtlasFrame>( this ,FName(Name) );

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
