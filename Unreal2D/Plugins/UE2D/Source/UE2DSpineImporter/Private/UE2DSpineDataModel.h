// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpineAtlasReader.h"

//#include "UE2DSpineDataModel.generated.h"


struct FUE2DSpineAtlasRegion
{

	FUE2DSpineAtlasRegion();

	FString Name;

	// Full frame bounds
	int BoundX , BoundY , BoundWidth , BoundHeight;

	float offsetX , offsetY;
	int originalWidth , originalHeight;
	int degrees;

	bool rotated;


	void Parse( FUE2DSpineAtlasReader& Reader );

};

struct FUE2DSpineAtlasPage
{
	// name of the Texture
	FString TextureName;

	// The different regions presents in the page
	TArray<FUE2DSpineAtlasRegion> Regions;


	void Parse( FUE2DSpineAtlasReader& Reader );

};


struct FUE2DSpineAtlas
{
	TArray<FUE2DSpineAtlasPage> Pages;

	void Load( const FString& InFilepath );
};
