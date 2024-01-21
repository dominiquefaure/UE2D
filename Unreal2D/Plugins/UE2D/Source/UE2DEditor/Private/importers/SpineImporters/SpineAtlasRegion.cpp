// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "SpineAtlasRegion.h"



//-------------------------------------------------------------------------------------------
FSpineAtlasRegion::FSpineAtlasRegion()
{
	BoundX			=	0;
	BoundY			=	0;
	BoundWidth		=	0;
	BoundHeight		=	0;
	offsetX			=	0;
	offsetY			=	0;

	rotated		=	false;
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FSpineAtlasRegion::Parse( FSpineAtlasReader& Reader )
{
	Name	=	Reader.GetString( true );

	TArray<int>EntryValues;
	FString EntryString;

	// skip region detail for the moment
	while( ( !Reader.IsFinished() ) && Reader.IsValuesLine() )
	{
		Reader.GetValues( &EntryString , &EntryValues , true );

		if( EntryString == "bounds" )
		{
			BoundX			=	EntryValues[ 0 ];
			BoundY			=	EntryValues[ 1 ];
			BoundWidth		=	EntryValues[ 2 ];
			BoundHeight		=	EntryValues[ 3 ];
		}
		if( EntryString == "offsets" )
		{
			offsetX			=	EntryValues[ 0 ];
			offsetY			=	EntryValues[ 1 ];
			originalWidth	=	EntryValues[ 2 ];
			originalHeight	=	EntryValues[ 3 ];
		}
		if( EntryString == "rotate" )
		{
			rotated		=	true;
		}
		EntryValues.Empty();
	}

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
void FSpineAtlasRegion::Apply( UUE2DTextureAtlas* DestAtlas , int TextureIndex )
{

	if( rotated )
	{
		DestAtlas->AddFrame( Name , TextureIndex , BoundX , BoundY , BoundHeight , BoundWidth , true );
	}
	else
	{
		DestAtlas->AddFrame( Name , TextureIndex , BoundX , BoundY , BoundWidth , BoundHeight , false );
	}
}
//-------------------------------------------------------------------------------------------
