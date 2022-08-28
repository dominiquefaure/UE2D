// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "UE2DSpriteAtlas.h"
#include "UE2DStructs.h"


struct FColor;



/**
* information to required for a sprite drawCall
*/
class FUE2DSpriteDrawRecord
{
public:

	FUE2DSpriteDrawRecord();
	~FUE2DSpriteDrawRecord();

	void Set( UUE2DSpriteAtlas* Atlas, uint32 FrameIndex , FColor InColor , UMaterialInterface* InMaterial );
	void Set( UUE2DSpriteAtlasFrame* Frame , FColor InColor , UMaterialInterface* InMaterial );

	void Set( UUE2DSpriteAtlasFrame* Frame , FColor InColor , FTransform InTransform, UMaterialInterface* InMaterial );

	void Apply( FStaticMeshVertexBuffers& InVertexBuffers )const;

private:

	void ComputeVertices( UUE2DSpriteAtlasFrame* InFrame );
	void ComputeVertices( UUE2DSpriteAtlasFrame* InFrame , FTransform InTransform );

public:

	// the Material to use
	UMaterialInterface*		Material;

	// list of unique vertices
	TArray<FUE2DSpriteVertex>	Vertices;

	FColor Color;
};