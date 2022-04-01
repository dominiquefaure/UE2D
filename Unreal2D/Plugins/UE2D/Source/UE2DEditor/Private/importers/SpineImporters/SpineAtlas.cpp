#include "SpineAtlas.h"

#include "SpineAtlasReader.h"

//-------------------------------------------------------------------------------------------
void FSpineAtlas::Load( const FString& InFilepath )
{
	FSpineAtlasReader Reader;

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
		FSpineAtlasPage Page;
		Page.Parse( Reader );

		// add the region to the list
		Pages.Add( Page );
	}

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FSpineAtlas::Apply( UUE2DSpriteAtlas* DestAtlas )
{
	// Clear the array
	DestAtlas->Frames.Empty();

	for( int i = 0; i < Pages.Num() ; i ++ )
	{
		Pages[ i ].Apply( DestAtlas );
	}
}
//-------------------------------------------------------------------------------------------
