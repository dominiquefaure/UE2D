#include "UE2DSpriteAtlasRenderProxy.h"


//------------------------------------------------------------------------------------------------
FUE2DSpriteAtlasRenderSceneProxy::FUE2DSpriteAtlasRenderSceneProxy( const UUE2DSpriteAtlasComponent* InComponent , uint32 InMaxSpriteNum ):
FPrimitiveSceneProxy(InComponent),
OwnerComponent( InComponent ),
MaxSpriteNum( InMaxSpriteNum ),
VertexFactory(GetScene().GetFeatureLevel(), "FASSpriteAtlasRenderSceneProxy"),
Renderer( GetScene().GetFeatureLevel() )
{
	// FPrimitiveSceneProxy
	bWillEverBeLit											=	false;

	bVerifyUsedMaterials = false;

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FUE2DSpriteAtlasRenderSceneProxy::~FUE2DSpriteAtlasRenderSceneProxy()
{
	VertexBuffers.PositionVertexBuffer.ReleaseResource();
	VertexBuffers.StaticMeshVertexBuffer.ReleaseResource();
	VertexBuffers.ColorVertexBuffer.ReleaseResource();

	IndexBuffer.ReleaseResource();
	VertexFactory.ReleaseResource();

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
SIZE_T FUE2DSpriteAtlasRenderSceneProxy::GetTypeHash() const
{
	static size_t UniquePointer;
	return reinterpret_cast<size_t>(&UniquePointer);
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
uint32 FUE2DSpriteAtlasRenderSceneProxy::GetMemoryFootprint() const
{
	return ( sizeof( this ) + FPrimitiveSceneProxy::GetAllocatedSize() );
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasRenderSceneProxy::CreateRenderThreadResources( )
{
	IndexBuffer.NumSprites									=	MaxSpriteNum;
	IndexBuffer.InitResource();

	VertexBuffers.InitWithDummyData(&VertexFactory, MaxSpriteNum * 4 , 2);

	Renderer.InitResources( 128 );
}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
FPrimitiveViewRelevance FUE2DSpriteAtlasRenderSceneProxy::GetViewRelevance( const FSceneView* View ) const
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
void FUE2DSpriteAtlasRenderSceneProxy::GetDynamicMeshElements( const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector ) const
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
	//	if( RenderBatch.Material->GetName() != TEXT( "None" ) )
		{
		//	MaterialProxy	=	RenderBatch.Material->GetRenderProxy();
			MaterialProxy	=	OwnerComponent->GetMaterial( 0 )->GetRenderProxy();
		}
	}

	for( int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++ )
	{
		if( VisibilityMap & (1 << ViewIndex) )
		{

			Renderer.Render( Collector , ViewIndex , IsLocalToWorldDeterminantNegative() , MaterialProxy  );

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
void FUE2DSpriteAtlasRenderSceneProxy::SetDynamicData_RenderThread( const TArray<FUE2DSpriteRenderCommand>& CommandList , bool MaterialListChanged )
{
	Renderer.ProcessCommands( CommandList );
}
//------------------------------------------------------------------------------------------------
