#include "SpineAtlasRegion.h"



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
			X			=	EntryValues[ 0 ];
			Y			=	EntryValues[ 1 ];
			Width		=	EntryValues[ 2 ];
			Height		=	EntryValues[ 3 ];
		}

	}

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
void FSpineAtlasRegion::Apply( UUE2DSpriteAtlas* DestAtlas )
{


	DestAtlas->AddFrame( Name , X , Y , Width , Height );
}
//-------------------------------------------------------------------------------------------
