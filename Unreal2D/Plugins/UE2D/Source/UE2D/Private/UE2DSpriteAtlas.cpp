// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlas.h"

//---------------------------------------------------------------------------------------------
FUE2DSpriteAtlasFrame* UUE2DSpriteAtlas::GetFrameAt( int32 Index )
{
	if( (Index >= 0 ) && (Index < Frames.Num() ) )
	{
		return &Frames[ Index ];
	}

	// not found
	return nullptr;
}
//---------------------------------------------------------------------------------------------

