// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "Sprites/UE2DSpriteAtlas.h"
#include "UE2DStructs.h"
#include "LocalVertexFactory.h"


class FUE2DSpriteRenderCommand;



/**
* Class responsible to render Sprites for a RenderProxy
*/
class FUE2DSpriteRenderer
{
public:

	FUE2DSpriteRenderer( ERHIFeatureLevel::Type InFeatureLevel );
	~FUE2DSpriteRenderer();


	void InitResources( const uint32 InMaxSpriteCount );


	void ProcessCommands( const TArray<FUE2DSpriteRenderCommand>& CommandList );

	// Perform the render operation
	void Render( FMeshElementCollector& Collector , int ViewIndex , bool ReverseCulling , FMaterialRenderProxy* TmpMaterial )const;


// Methods
private:

	void ProcessCommand( const FUE2DSpriteRenderCommand& Command , uint32& VertexIndex );

	void FlushVertexBuffers( uint32 VerticeCount );

// properties
private:

	// Buffers Max Size
	uint32							MaxSpriteCount;

	// Render Resources
	FLocalVertexFactory				VertexFactory;
	FUE2DQuadSpriteIndexBuffer		IndexBuffer;
	FStaticMeshVertexBuffers		VertexBuffers;

	TArray<FUE2DSpriteRenderBatch>	RenderBatches;
};