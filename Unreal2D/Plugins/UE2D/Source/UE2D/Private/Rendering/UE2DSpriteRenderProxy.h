// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimitiveSceneProxy.h"
#include "Components/UE2DSpriteAtlasComponent.h"

#include "LocalVertexFactory.h"
#include "UE2DQuadSpriteIndexBuffer.h"
#include "UE2DStructs.h"
#include "Rendering/UE2DSpriteRenderCommandBuilder.h"
#include "Rendering/UE2DSpriteRenderer.h"

class FUE2DSpriteRenderCommandBuilder;


/**
 * render Proxy for Sprites based rendering
 */
class FUE2DSpriteRenderSceneProxy : public FPrimitiveSceneProxy
{
public:
	FUE2DSpriteRenderSceneProxy( const UUE2DSceneComponent* InComponent ,  uint32 InMaxSpriteNum = 128 );
	virtual ~FUE2DSpriteRenderSceneProxy();

// Overrides
public:

	// FPrimitiveSceneProxy interface
	virtual SIZE_T GetTypeHash() const override;
	virtual void CreateRenderThreadResources() override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;
	virtual uint32 GetMemoryFootprint() const override;


	void SetDynamicData_RenderThread( const TArray<FUE2DSpriteRenderCommand>& CommandList , bool MaterialListChanged );

private:

	void GetViewDynamicMeshElements( const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector )const;
	void GetViewWireframeDynamicMeshElements( const FSceneView* View, int32 ViewIndex, FMeshElementCollector& Collector , const FColoredMaterialRenderProxy* WireframeMaterialInstance)const;


private:

	const UUE2DSceneComponent*		OwnerComponent;


	// Buffers Max Size
	uint32							MaxSpriteNum;

	/*// Render Resources
	FLocalVertexFactory				VertexFactory;
	FUE2DQuadSpriteIndexBuffer		IndexBuffer;
	FStaticMeshVertexBuffers		VertexBuffers;
*/

	FUE2DSpriteRenderer		Renderer;

};
