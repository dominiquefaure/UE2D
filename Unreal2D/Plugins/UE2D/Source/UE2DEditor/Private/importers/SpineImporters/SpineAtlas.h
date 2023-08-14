#pragma once

#include "CoreMinimal.h"

#include "SpineAtlasPage.h"
#include "SpineAtlasRegion.h"
#include "TextureAtlas/UE2DTextureAtlas.h"


class FSpineAtlas
{

public:

	void Load( const FString& InFilepath );


	void Apply( UUE2DTextureAtlas* DestAtlas );

private:

	TArray<FSpineAtlasPage> Pages;

};
