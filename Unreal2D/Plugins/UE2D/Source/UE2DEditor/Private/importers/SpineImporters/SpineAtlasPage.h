
#pragma once

#include "CoreMinimal.h"
#include "SpineAtlasRegion.h"

#include "SpineAtlasReader.h"
#include "TextureAtlas/UE2DTextureAtlas.h"


class FSpineAtlasPage
{

public:

	void Parse( FSpineAtlasReader& Reader );

	void Apply( UUE2DTextureAtlas* DestAtlas );


private:

	// name of the Texture
	FString TextureName;

	// The different regions presents in the page
	TArray<FSpineAtlasRegion> Regions;

};