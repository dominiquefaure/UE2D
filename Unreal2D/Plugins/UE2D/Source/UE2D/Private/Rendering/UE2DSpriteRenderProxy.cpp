// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "UE2DSpriteRenderProxy.h"


//------------------------------------------------------------------------------------------------
FUE2DSpriteRenderSceneProxy::FUE2DSpriteRenderSceneProxy( const UUE2DSceneComponent* InComponent , uint32 InMaxSpriteNum ):
FPrimitiveSceneProxy(InComponent),
OwnerComponent( InComponent ),
MaxSpriteNum( InMaxSpriteNum ),
Renderer( InComponent->GetWorld()->GetFeatureLevel() )
{
	SetWireframeColor( FLinearColor::White );

	// FPrimitiveSceneProxy
	bWillEverBeLit											=	false;

	bVerifyUsedMaterials = false;

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FUE2DSpriteRenderSceneProxy::~FUE2DSpriteRenderSceneProxy()
{
/*	VertexBuffers.PositionVertexBuffer.ReleaseResource();
	VertexBuffers.StaticMeshVertexBuffer.ReleaseResource();
	VertexBuffers.ColorVertexBuffer.ReleaseResource();

	IndexBuffer.ReleaseResource();
	VertexFactory.ReleaseResource();
*/
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
SIZE_T FUE2DSpriteRenderSceneProxy::GetTypeHash() const
{
	static size_t UniquePointer;
	return reinterpret_cast<size_t>(&UniquePointer);
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
uint32 FUE2DSpriteRenderSceneProxy::GetMemoryFootprint() const
{
	return ( sizeof( this ) + FPrimitiveSceneProxy::GetAllocatedSize() );
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void FUE2DSpriteRenderSceneProxy::CreateRenderThreadResources( FRHICommandListBase& RHICmdList )
{
	Renderer.InitResources( RHICmdList , 128 );
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FPrimitiveViewRelevance FUE2DSpriteRenderSceneProxy::GetViewRelevance( const FSceneView* View ) const
{
	FPrimitiveViewRelevance Result;

	Result.bDrawRelevance        = IsShown(View);
	Result.bRenderCustomDepth    = ShouldRenderCustomDepth();
	Result.bRenderInMainPass     = ShouldRenderInMainPass();
	Result.bUsesLightingChannels = false;
	Result.bOpaque               = true;
	Result.bSeparateTranslucency = true;
	Result.bNormalTranslucency   = false;
	Result.bShadowRelevance      = IsShadowCast(View);
	Result.bDynamicRelevance     = true;

	return Result;
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void FUE2DSpriteRenderSceneProxy::GetDynamicMeshElements( const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector ) const
{
	const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;
	FMaterialRenderProxy* MaterialProxy						=	NULL;

	if(bWireframe)
	{
		FColoredMaterialRenderProxy* WireframeMaterialInstance = new FColoredMaterialRenderProxy(
			GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy() : NULL,
			FLinearColor(0, 0.5f, 1.f)
		);
		Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
		MaterialProxy = WireframeMaterialInstance;
	}
	else
	{
		if( OwnerComponent->GetMaterial( 0 ) != nullptr )
		{
		//	MaterialProxy	=	RenderBatch.Material->GetRenderProxy();
			MaterialProxy	=	OwnerComponent->GetMaterial( 0 )->GetRenderProxy();
		}
	}

	for( int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++ )
	{
		if( VisibilityMap & (1 << ViewIndex) )
		{
			Renderer.Render( Collector , ViewIndex , IsLocalToWorldDeterminantNegative() , MaterialProxy );
//			RenderBatches( Collector , ViewIndex , IsLocalToWorldDeterminantNegative() , MaterialProxy  );

			/*

			#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
						// Render bounds
						RenderBounds( Collector.GetPDI( ViewIndex ), ViewFamily.EngineShowFlags, GetBounds(), IsSelected() );
			#endif
			*/
		}
	}

}
//------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
void FUE2DSpriteRenderSceneProxy::SetDynamicData_RenderThread( FRHICommandListBase& RHICmdList , const TArray<FUE2DSpriteRenderCommand>& CommandList , bool MaterialListChanged )
{
	if( OwnerComponent->GetMaterial( 0 ) != nullptr )
	{
		Renderer.SetDefaultMaterialProxy( OwnerComponent->GetMaterial( 0 )->GetRenderProxy() );
		Renderer.ProcessCommands( RHICmdList , CommandList );
	}

}
//------------------------------------------------------------------------------------------------
