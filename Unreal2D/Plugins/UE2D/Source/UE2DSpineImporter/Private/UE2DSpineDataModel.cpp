
#include "UE2DSpineDataModel.h"


//-------------------------------------------------------------------------------------------
FUE2DSpineAtlasRegion::FUE2DSpineAtlasRegion()
{

	BoundX			=	0;
	BoundY			=	0;
	BoundWidth		=	0;
	BoundHeight		=	0;
	offsetX			=	0;
	offsetY			=	0;

	rotated			=	false;

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpineAtlasRegion::Parse( FUE2DSpineAtlasReader& Reader )
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
void FUE2DSpineAtlasPage::Parse( FUE2DSpineAtlasReader& Reader )
{
	// get the name of the texture
	TextureName	=	Reader.GetString( true );

	// skip Texture details for the moment
	while( ( !Reader.IsFinished() ) && Reader.IsValuesLine() )
	{
		Reader.AdvanceLine();
	}

	while( !Reader.IsFinished() )
	{
		// if it's a separator , page is finished
		if( Reader.IsEmptyLine() )
		{
			break;
		}

		// read the next region data
		FUE2DSpineAtlasRegion Region;
		Region.Parse( Reader );

		// add the region to the list
		Regions.Add( Region );
	}
}
//-------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------
void FUE2DSpineAtlas::Load( const FString& InFilepath )
{
	FUE2DSpineAtlasReader Reader;

	Reader.Load( InFilepath );


	while( !Reader.IsFinished() )
	{
		// skip separators
		if( Reader.IsEmptyLine() )
		{
			Reader.AdvanceLine();
			continue;
		}

		// read the next region data
		FUE2DSpineAtlasPage Page;
		Page.Parse( Reader );

		// add the region to the list
		Pages.Add( Page );
	}

}
//-------------------------------------------------------------------------------------------
