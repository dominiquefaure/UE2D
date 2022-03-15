#include "UE2DSpriteAtlasRenderProxy.h"
#include "UE2DSpriteDrawRecord.h"


//------------------------------------------------------------------------------------------------
FUE2DSpriteAtlasRenderSceneProxy::FUE2DSpriteAtlasRenderSceneProxy( const UUE2DSpriteAtlasComponent* InComponent , uint32 InMaxSpriteNum ):
FPrimitiveSceneProxy(InComponent),
MaxSpriteNum( InMaxSpriteNum ),
VertexFactory(GetScene().GetFeatureLevel(), "FASSpriteAtlasRenderSceneProxy")
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
	if( RenderBatch.Material == nullptr )
	{
		return;
	}

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
		MaterialProxy	=	RenderBatch.Material->GetRenderProxy();
	}

	for( int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++ )
	{
		if( VisibilityMap & (1 << ViewIndex) )
		{
			// Draw the mesh. 
			FMeshBatch& Mesh				=	Collector.AllocateMesh();
			Mesh.VertexFactory				=	&VertexFactory;
			Mesh.MaterialRenderProxy		=	MaterialProxy;
			Mesh.ReverseCulling				=	IsLocalToWorldDeterminantNegative();
			Mesh.CastShadow					=	false;
			Mesh.DepthPriorityGroup			=	SDPG_World;
			Mesh.Type						=	PT_TriangleList;
			Mesh.bDisableBackfaceCulling	=	true;
			Mesh.bCanApplyViewModeOverrides =	false;

			FMeshBatchElement& BatchElement =	Mesh.Elements[0];
			BatchElement.IndexBuffer		=	&IndexBuffer;
			BatchElement.FirstIndex			=	RenderBatch.FirstIndex;
			BatchElement.MinVertexIndex		=	RenderBatch.MinVertexIndex;
			BatchElement.MaxVertexIndex		=	RenderBatch.MaxVertexIndex;
			BatchElement.NumPrimitives		=	RenderBatch.NumPrimitives;
			Collector.AddMesh( ViewIndex, Mesh );

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
			// Render bounds
			RenderBounds( Collector.GetPDI( ViewIndex ), ViewFamily.EngineShowFlags, GetBounds(), IsSelected() );
#endif
		}
	}

}
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasRenderSceneProxy::SetDynamicData_RenderThread( const FUE2DSpriteDrawRecord& Record )
{
	check(IsInRenderingThread());

	Record.Apply( VertexBuffers );

	// Apply the values set to the RHI
	uint32 verticeCount	=	4;
	{
		auto& VertexBuffer = VertexBuffers.PositionVertexBuffer;
		void* VertexBufferData = RHILockBuffer(VertexBuffer.VertexBufferRHI, 0, verticeCount * VertexBuffer.GetStride(), RLM_WriteOnly);
		FMemory::Memcpy(VertexBufferData, VertexBuffer.GetVertexData(), verticeCount * VertexBuffer.GetStride());
		RHIUnlockBuffer(VertexBuffer.VertexBufferRHI);
	}
	{
		auto& VertexBuffer = VertexBuffers.StaticMeshVertexBuffer;
		void* VertexBufferData = RHILockBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI, 0, VertexBuffer.GetTexCoordSize(), RLM_WriteOnly);
		FMemory::Memcpy(VertexBufferData, VertexBuffer.GetTexCoordData(), VertexBuffer.GetTexCoordSize());
		RHIUnlockBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI);
	}


	RenderBatch.Material		=	Record.Material;
	RenderBatch.FirstIndex		=	0;
	RenderBatch.MaxIndex		=	5;
	RenderBatch.NumPrimitives	=	2;
	RenderBatch.MinVertexIndex	=	0;
	RenderBatch.MaxVertexIndex	=	3;
}
//------------------------------------------------------------------------------------------------

