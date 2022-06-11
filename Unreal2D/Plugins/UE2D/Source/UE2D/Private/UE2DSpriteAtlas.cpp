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
void UUE2DSpriteAtlas::AddFrame( FString Name , int SrcX , int SrcY , int Width , int Height , bool InRotate )
{
	UUE2DSpriteAtlasFrame* Frame	=	NewObject<UUE2DSpriteAtlasFrame>( this );

	Frame->Name		=	Name;
	Frame->X		=	SrcX;
	Frame->Y		=	SrcY;
	Frame->Width	=	Width;
	Frame->Height	=	Height;
	Frame->Rotated	=	InRotate;

	Frames.Add( Frame );
}
//---------------------------------------------------------------------------------------------
