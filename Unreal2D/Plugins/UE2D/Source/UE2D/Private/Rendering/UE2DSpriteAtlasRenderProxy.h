// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimitiveSceneProxy.h"
#include "UE2DSpriteAtlasComponent.h"

#include "LocalVertexFactory.h"
#include "UE2DQuadSpriteIndexBuffer.h"

class FUE2DSpriteDrawRecord;


/*
* Contain the necessary parameters to perform a draw call
*/
struct FUE2DSpriteRenderBatch
{
	FUE2DSpriteRenderBatch()
	{
		Material	=	nullptr;
	}

	// The Material to use for the Whole Batch
	UMaterialInterface* Material;

	// The texture to use for the Section ( Override Material parameter )
	//	UTexture* Texture;

	// First Index in the IndexBuffer
	uint32 FirstIndex;
	uint32 MaxIndex;

	// Number of primitive to draw
	uint32 NumPrimitives;
	uint32 MinVertexIndex;
	uint32 MaxVertexIndex;
};


/**
 * 
 */
class FUE2DSpriteAtlasRenderSceneProxy : public FPrimitiveSceneProxy
{
public:
	FUE2DSpriteAtlasRenderSceneProxy( const UUE2DSpriteAtlasComponent* InComponent ,  uint32 InMaxSpriteNum = 1 );
	virtual ~FUE2DSpriteAtlasRenderSceneProxy();

// Overrides
public:

	// FPrimitiveSceneProxy interface
	virtual SIZE_T GetTypeHash() const override;
	virtual void CreateRenderThreadResources() override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;
	virtual uint32 GetMemoryFootprint() const override;


	void SetDynamicData_RenderThread(const FUE2DSpriteDrawRecord& Record );

private:

	void GetViewDynamicMeshElements( const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector )const;
	void GetViewWireframeDynamicMeshElements( const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector , const FColoredMaterialRenderProxy* WireframeMaterialInstance)const;


private:


	// Buffers Max Size
	uint32 MaxSpriteNum;

	// Render Resources
	FLocalVertexFactory			VertexFactory;
	FUE2DQuadSpriteIndexBuffer	IndexBuffer;
	FStaticMeshVertexBuffers	VertexBuffers;


	FUE2DSpriteRenderBatch		RenderBatch;
};
