
#pragma once

#include "CoreMinimal.h"
#include "SpineAtlasRegion.h"

#include "SpineAtlasReader.h"
#include "UE2DSpriteAtlas.h"


class FSpineAtlasPage
{

public:

	void Parse( FSpineAtlasReader& Reader );

	void Apply( UUE2DSpriteAtlas* DestAtlas );


private:

	// name of the Texture
	FString TextureName;

	// The different regions presents in the page
	TArray<FSpineAtlasRegion> Regions;

};