
#pragma once

#include "CoreMinimal.h"
#include "SpineAtlasReader.h"
#include "Sprites/UE2DSpriteAtlas.h"

class FSpineAtlasRegion
{
public:

	FSpineAtlasRegion();

	void Parse(FSpineAtlasReader& Reader );
	void Apply( UUE2DSpriteAtlas* DestAtlas , int TextureIndex );

private:
	FString Name;
	
	// Full frame bounds
	int BoundX , BoundY , BoundWidth , BoundHeight;

	float offsetX , offsetY;
	int originalWidth , originalHeight;
	int degrees;

	bool rotated;

};