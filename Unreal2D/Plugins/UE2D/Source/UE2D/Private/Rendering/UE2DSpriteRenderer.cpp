// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

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

	MaterialMap.Empty();
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::InitResources( FRHICommandListBase& RHICmdList , const uint32 InMaxSpriteCount )
{
	MaxSpriteCount											=	InMaxSpriteCount;

	IndexBuffer.NumSprites									=	InMaxSpriteCount;
	IndexBuffer.InitResource( RHICmdList );

	VertexBuffers.InitWithDummyData( RHICmdList  , &VertexFactory , MaxSpriteCount * 4 , 2 );
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::SetDefaultMaterialProxy( FMaterialRenderProxy* Material )
{
	DefaultMaterialProxy				=	Material;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::ProcessCommands( FRHICommandListBase& RHICmdList , const TArray<FUE2DSpriteRenderCommand>& CommandList )
{
	StartProcessCommands();

	uint32 VertexIndex					=	0;

	int CommandCount					=	CommandList.Num();
	for( int i = 0 ; i < CommandCount ; i ++ )
	{
		ProcessCommand( CommandList[i] , VertexIndex );
	}

	FlushVertexBuffers( RHICmdList , VertexIndex );
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::FlushVertexBuffers( FRHICommandListBase& RHICmdList , uint32 VerticeCount )
{
	// flush Position
	{
		auto& VertexBuffer = VertexBuffers.PositionVertexBuffer;
		void* VertexBufferData = RHICmdList.LockBuffer( VertexBuffer.VertexBufferRHI , 0 , VerticeCount * VertexBuffer.GetStride() , RLM_WriteOnly );
		FMemory::Memcpy( VertexBufferData , VertexBuffer.GetVertexData() , VerticeCount * VertexBuffer.GetStride() );
		RHICmdList.UnlockBuffer( VertexBuffer.VertexBufferRHI );
	}

	// Flus colors
	{
		auto& VertexBuffer = VertexBuffers.ColorVertexBuffer;
		void* VertexBufferData = RHICmdList.LockBuffer( VertexBuffer.VertexBufferRHI , 0 , VertexBuffer.GetNumVertices() * VertexBuffer.GetStride() , RLM_WriteOnly );
		FMemory::Memcpy( VertexBufferData , VertexBuffer.GetVertexData() , VertexBuffer.GetNumVertices() * VertexBuffer.GetStride() );
		RHICmdList.UnlockBuffer( VertexBuffer.VertexBufferRHI );
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
		void* VertexBufferData = RHICmdList.LockBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI, 0, VertexBuffer.GetTexCoordSize(), RLM_WriteOnly);
		FMemory::Memcpy(VertexBufferData, VertexBuffer.GetTexCoordData(), VertexBuffer.GetTexCoordSize());
		RHICmdList.UnlockBuffer(VertexBuffer.TexCoordVertexBuffer.VertexBufferRHI);
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
		Mesh.MaterialRenderProxy		=	RenderBatch->MaterialProxy;
//		Mesh.MaterialRenderProxy		=	TmpMaterial;
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


//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::StartProcessCommands()
{
	// Clear the render batch list
	RenderBatches.Empty();

	CurrentIndexBufferCount					=	0;
	VertexBufferCount						=	0;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderer::ProcessCommand( const FUE2DSpriteRenderCommand& Command , uint32& VertexIndex )
{
	// Always create a new Batch at the moment
	FUE2DSpriteRenderBatch RenderBatch;

	RenderBatch.FirstIndex					=	CurrentIndexBufferCount;
	RenderBatch.MinVertexIndex				=	VertexIndex;

	const UTexture* Texture					=	Command.GetTexture();
	RenderBatch.MaterialProxy				=	GetMaterialProxy( Texture );

	Command.WriteToVertexBuffer( VertexBuffers , VertexIndex );

	// increase the number of Elements used in the index buffer
	CurrentIndexBufferCount					+=	6;

	RenderBatch.MaxIndex					=	CurrentIndexBufferCount;
	RenderBatch.NumPrimitives				=	2;
	RenderBatch.MaxVertexIndex				=	VertexIndex - 1;

	// Add the Batch to the List
	RenderBatches.Add( RenderBatch );
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
FMaterialRenderProxy* FUE2DSpriteRenderer::GetMaterialProxy( const UTexture* Texture )
{
	FMaterialRenderProxy** Result						=	MaterialMap.Find( Texture );

	if( Result )
	{
		return *Result;
	}

	FMaterialRenderProxy* NewProxy						=	new FColoredTexturedMaterialRenderProxy( DefaultMaterialProxy ,
																									FLinearColor::White ,
																									NAME_Color ,
																									Texture , FName( TEXT( "SpriteTexture" ) ) );


	MaterialMap.Add( Texture , NewProxy );

	return NewProxy;
}
//--------------------------------------------------------------------------------------
