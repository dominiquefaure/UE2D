// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SpineAtlasReader.h"
#include "TextureAtlas/UE2DTextureAtlas.h"

class FSpineAtlasRegion
{
public:

	FSpineAtlasRegion();

	void Parse(FSpineAtlasReader& Reader );
	void Apply( UUE2DTextureAtlas* DestAtlas , int TextureIndex );

private:
	FString Name;
	
	// Full frame bounds
	int BoundX , BoundY , BoundWidth , BoundHeight;

	float offsetX , offsetY;
	int originalWidth , originalHeight;
	int degrees;

	bool rotated;

};