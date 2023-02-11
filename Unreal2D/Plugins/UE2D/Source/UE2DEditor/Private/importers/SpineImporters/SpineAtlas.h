#pragma once

#include "CoreMinimal.h"

#include "SpineAtlasPage.h"
#include "SpineAtlasRegion.h"
#include "Sprites/UE2DSpriteAtlas.h"


class FSpineAtlas
{

public:

	void Load( const FString& InFilepath );


	void Apply( UUE2DSpriteAtlas* DestAtlas );

private:

	TArray<FSpineAtlasPage> Pages;

};
