#include "SpineAtlasPage.h"

void FSpineAtlasPage::Parse( FSpineAtlasReader& Reader )
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
		FSpineAtlasRegion Region;
		Region.Parse( Reader );

		// add the region to the list
		Regions.Add( Region );
	}
}


//-------------------------------------------------------------------------------------------
void FSpineAtlasPage::Apply( UUE2DSpriteAtlas* DestAtlas )
{

	int TextureIndex	=	0;

	for( int i = 0; i < Regions.Num(); i++ )
	{
		Regions[ i ].Apply( DestAtlas , TextureIndex );
	}
}
//-------------------------------------------------------------------------------------------
