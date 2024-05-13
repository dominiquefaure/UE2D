// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "TextureAtlas/UE2DTextureAtlas.h"
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


	void InitResources( FRHICommandListBase& RHICmdList , const uint32 InMaxSpriteCount );


	void SetDefaultMaterialProxy( FMaterialRenderProxy* Material );

	void ProcessCommands( FRHICommandListBase& RHICmdList ,const TArray<FUE2DSpriteRenderCommand>& CommandList );

	// Perform the render operation
	void Render( FMeshElementCollector& Collector , int ViewIndex , bool ReverseCulling , FMaterialRenderProxy* TmpMaterial )const;


// Methods
private:

	void ProcessCommand( const FUE2DSpriteRenderCommand& Command , uint32& VertexIndex );

	void FlushVertexBuffers( FRHICommandListBase& RHICmdList , uint32 VerticeCount );

	// call when start to process the different Commands, reset internal values
	void StartProcessCommands();


	FMaterialRenderProxy* GetMaterialProxy( const UTexture* Texture );

// properties
private:

	// Buffers Max Size
	uint32							MaxSpriteCount;

	// Render Resources
	FLocalVertexFactory				VertexFactory;
	FUE2DQuadSpriteIndexBuffer		IndexBuffer;
	FStaticMeshVertexBuffers		VertexBuffers;

	TArray<FUE2DSpriteRenderBatch>	RenderBatches;


	// Temp variables used to define the Batches content
	int								CurrentIndexBufferCount;
	int								VertexBufferCount;


	FMaterialRenderProxy*			DefaultMaterialProxy;

	TMap<const UTexture* , FMaterialRenderProxy*> MaterialMap;
};