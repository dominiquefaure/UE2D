
#pragma once

#include "CoreMinimal.h"
#include "SpineAtlasReader.h"
#include "UE2DSpriteAtlas.h"

class FSpineAtlasRegion
{
public:



	void Parse(FSpineAtlasReader& Reader );
	void Apply( UUE2DSpriteAtlas* DestAtlas );

private:
	FString Name;
	int X , Y , Width , Height; // Bounds
	float offsetX , offsetY;
	int originalWidth , originalHeight;
	int degrees;

};