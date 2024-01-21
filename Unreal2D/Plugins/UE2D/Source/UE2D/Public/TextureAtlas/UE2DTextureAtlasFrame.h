// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DStructs.h"


#include "UE2DTextureAtlasFrame.generated.h"

class UUE2DTextureAtlas;

UCLASS(hidecategories=Object, BlueprintType , Within=UE2DTextureAtlas)
class UE2D_API UUE2DTextureAtlasFrame : public UObject
{
	friend class UUE2DTextureAtlas;

	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere )
	FString Name;

	// The texture to use
	UPROPERTY(  EditAnywhere )
	UTexture* Texture;

	// Start X position in the Texture
	UPROPERTY( EditAnywhere)
	int32 X;

	// Start X position in the Texture
	UPROPERTY( EditAnywhere)
	int32 Y;

	// Frame Width
	UPROPERTY( EditAnywhere)
	int32 Width;

	// Frame Height
	UPROPERTY( EditAnywhere)
	int32 Height;

	UPROPERTY( EditAnywhere )
	bool Rotated;


	void GetVertices( TArray<FUE2DSpriteVertex>& OutVertices );
	const TArray<FUE2DSpriteVertex>&  GetVertices( );

private:

	// compute the vertices representing this Frame
	void ComputeVertices();


	// pre-computed vertices
	TArray< FUE2DSpriteVertex> Vertices;

};

