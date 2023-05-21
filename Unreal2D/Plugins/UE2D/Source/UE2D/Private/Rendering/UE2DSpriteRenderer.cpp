#include "UE2DSpriteRenderer.h"


//--------------------------------------------------------------------------------------
FUE2DSpriteRenderer::FUE2DSpriteRenderer( ERHIFeatureLevel::Type InFeatureLevel ):
	VertexFactory( InFeatureLevel , "FUE2DSpriteRenderer" )

{

}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
FUE2DSpriteRenderer::~FUE2DSpriteRenderer()
{
	VertexBuffers.PositionVertexBuffer.ReleaseResource();
	VertexBuffers.StaticMeshVertexBuffer.ReleaseResource();
	VertexBuffers.ColorVertexBuffer.ReleaseResource();

	IndexBuffer.ReleaseResource();
	VertexFactory.ReleaseResource();

}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::InitResources( const uint32 InMaxSpriteCount )
{
	MaxSpriteCount											=	InMaxSpriteCount;

	IndexBuffer.NumSprites									=	InMaxSpriteCount;
	IndexBuffer.InitResource();

	VertexBuffers.InitWithDummyData( &VertexFactory , MaxSpriteCount * 4 , 2 );

}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::ProcessCommands( const TArray<FUE2DSpriteRenderCommand>& CommandList )
{
	// Clear the render batch list
	RenderBatches.Empty();

	uint32 VertexIndex					=	0;

	int CommandCount					=	CommandList.Num();
	for( int i = 0 ; i < CommandCount ; i ++ )
	{
		ProcessCommand( CommandList[i] , VertexIndex );
	}

	FlushVertexBuffers( VertexIndex );

	FUE2DSpriteRenderBatch RenderBatch;
	RenderBatch.FirstIndex		=	0;
	RenderBatch.MaxIndex		=	5;
	RenderBatch.NumPrimitives	=	2;
	RenderBatch.MinVertexIndex	=	0;
	RenderBatch.MaxVertexIndex	=	3;

	RenderBatches.Add( RenderBatch );

	FUE2DSpriteRenderBatch RenderBatch2;
	RenderBatch2.FirstIndex		=	6;
	RenderBatch2.MaxIndex		=	11;
	RenderBatch2.NumPrimitives	=	2;
	RenderBatch2.MinVertexIndex	=	4;
	RenderBatch2.MaxVertexIndex	=	7;

	RenderBatches.Add( RenderBatch2 );
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::ProcessCommand( const FUE2DSpriteRenderCommand& Command , uint32& VertexIndex )
{
	Command.WriteToVertexBuffer( VertexBuffers , VertexIndex );
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::FlushVertexBuffers( uint32 VerticeCount )
{
	// flush Position
	{
		auto& VertexBuffer = VertexBuffers.PositionVertexBuffer;
		void* VertexBufferData = RHILockBuffer( VertexBuffer.VertexBufferRHI , 0 , VerticeCount * VertexBuffer.GetStride() , RLM_WriteOnly );
		FMemory::Memcpy( VertexBufferData , VertexBuffer.GetVertexData() , VerticeCount * VertexBuffer.GetStride() );
		RHIUnlockBuffer( VertexBuffer.VertexBufferRHI );
	}

	// Flus colors
	{
		auto& VertexBuffer = VertexBuffers.ColorVertexBuffer;
		void* VertexBufferData = RHILockBuffer( VertexBuffer.VertexBufferRHI , 0 , VertexBuffer.GetNumVertices() * VertexBuffer.GetStride() , RLM_WriteOnly );
		FMemory::Memcpy( VertexBufferData , VertexBuffer.GetVertexData() , VertexBuffer.GetNumVertices() * VertexBuffer.GetStride() );
		RHIUnlockBuffer( VertexBuffer.VertexBufferRHI );
	}

	/*	{
			auto& ColorBuffer = VertexBuffers.ColorVertexBuffer;
			void* VertexBufferData = RHILockBuffer( ColorBuffer.VertexBufferRHI, 0, verticeCount * ColorBuffer.GetStride(), RLM_WriteOnly);
			FMemory::Memcpy(VertexBufferData, ColorBuffer.GetVertexData(), verticeCount * ColorBuffer.GetStride());
			RHIUnlockBuffer( ColorBuffer.VertexBufferRHI);
		}
	*/

	
	// Flush Textures coordinates
	{
		auto& VertexBuffer = VertexBuffers.StaticMeshVertexBuffer;
		void* VertexBufferData = RHILockBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI, 0, VertexBuffer.GetTexCoordSize(), RLM_WriteOnly);
		FMemory::Memcpy(VertexBufferData, VertexBuffer.GetTexCoordData(), VertexBuffer.GetTexCoordSize());
		RHIUnlockBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI);
	}

}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::Render( FMeshElementCollector& Collector , int ViewIndex , bool ReverseCulling , FMaterialRenderProxy* TmpMaterial )const
{
	const FUE2DSpriteRenderBatch* RenderBatch;

	int Count							=	RenderBatches.Num();
	for( int i = 0 ; i < Count ; i ++ )
	{
		RenderBatch						=	&RenderBatches[ i ];

		// Draw the mesh. 
		FMeshBatch& Mesh				=	Collector.AllocateMesh();
		Mesh.VertexFactory				=	&VertexFactory;
//		Mesh.MaterialRenderProxy		=	RenderBatch->MaterialProxy;
		Mesh.MaterialRenderProxy		=	TmpMaterial;
		Mesh.ReverseCulling				=	ReverseCulling;
		Mesh.CastShadow					=	false;
		Mesh.DepthPriorityGroup			=	SDPG_World;
		Mesh.Type						=	PT_TriangleList;
		Mesh.bDisableBackfaceCulling	=	true;
		Mesh.bCanApplyViewModeOverrides =	false;

		FMeshBatchElement& BatchElement =	Mesh.Elements[ 0 ];
		BatchElement.IndexBuffer		=	&IndexBuffer;
		BatchElement.FirstIndex			=	RenderBatch->FirstIndex;
		BatchElement.MinVertexIndex		=	RenderBatch->MinVertexIndex;
		BatchElement.MaxVertexIndex		=	RenderBatch->MaxVertexIndex;
		BatchElement.NumPrimitives		=	RenderBatch->NumPrimitives;
		Collector.AddMesh( ViewIndex , Mesh );

	}
}
//--------------------------------------------------------------------------------------

