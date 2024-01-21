// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "TextureAtlas/UE2DTextureAtlas.h"
#include "UE2DStructs.h"

struct FColor;



/**
* Build a Collection of Draw commands to send to the render thread
*/
class FUE2DSpriteRenderCommand
{
public:

	FUE2DSpriteRenderCommand();
	~FUE2DSpriteRenderCommand();


	const UTexture* GetTexture()const
	{
		return Texture;
	}

	void Set( UUE2DTextureAtlasFrame* InFrame , FTransform InTransform , FColor InColor , UTexture* InTexture , float DeltaY );

	void WriteToVertexBuffer( FStaticMeshVertexBuffers& InVertexBuffers , uint32& VertexIndex )const;

// Methods
private:
	void ComputeVertices( UUE2DTextureAtlasFrame* InFrame , FTransform InTransform , float DeltaY );

// Fields
private:

	// the Texture to use
	UTexture*					Texture;

	// Color to Apply
	FColor						Color;

	// list of unique vertices
	TArray<FUE2DSpriteVertex>	Vertices;

};