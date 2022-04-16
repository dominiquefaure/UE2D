// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "UE2DSpriteAtlas.h"

/*
* Definition of a Vertex for an AsSprite
*/
struct FUE2DSpriteVertex
{
	FVector3f Position;
	FVector2f TexCoord;
};


/**
* information to required for a sprite drawCall
*/
class FUE2DSpriteDrawRecord
{
public:

	FUE2DSpriteDrawRecord();
	~FUE2DSpriteDrawRecord();

	void Set( UUE2DSpriteAtlas* Atlas, uint32 FrameIndex , UMaterialInterface* InMaterial );


	void Apply( FStaticMeshVertexBuffers& InVertexBuffers )const;

private:

	void ComputeVertices( UUE2DSpriteAtlas* Atlas, FUE2DSpriteAtlasFrame* InFrame );

public:

	// the Material to use
	UMaterialInterface*		Material;

	// list of unique vertices
	TArray<FUE2DSpriteVertex>	Vertices;
};