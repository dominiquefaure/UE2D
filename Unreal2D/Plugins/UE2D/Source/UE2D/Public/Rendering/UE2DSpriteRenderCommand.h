// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "Sprites/UE2DSpriteAtlas.h"
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


	void Set( UUE2DSpriteAtlasFrame* InFrame , FTransform InTransform , FColor InColor , uint32 MaterialIndex , float DeltaY );


	void WriteToVertexBuffer( FStaticMeshVertexBuffers& InVertexBuffers , uint32& VertexIndex )const;

// Methods
private:
	void ComputeVertices( UUE2DSpriteAtlasFrame* InFrame , FTransform InTransform , float DeltaY );

// Fields
private:

	// list of unique vertices
	TArray<FUE2DSpriteVertex>	Vertices;

	// Color to Apply
	FColor						Color;

	// Index of hte Material to use
	uint32						MaterialIndex;

};