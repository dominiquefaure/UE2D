#include "UE2DSpriteDrawRecord.h"

#include "UE2DSpriteAtlasFrame.h"

//--------------------------------------------------------------------------------------
FUE2DSpriteDrawRecord::FUE2DSpriteDrawRecord()
{
	Material	=	nullptr;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
FUE2DSpriteDrawRecord::~FUE2DSpriteDrawRecord( )
{


}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::Set( UUE2DSpriteAtlas* Atlas, uint32 FrameIndex, FColor InColor , UMaterialInterface* InMaterial )
{
	if( Atlas == nullptr )
	{
		return;
	}

	UUE2DSpriteAtlasFrame* Frame							=	Atlas->GetFrameAt( FrameIndex );

	if( Frame == nullptr )
	{
		return;
	}

	ComputeVertices( Frame );

	Material												=	InMaterial;
	Color													=	InColor;

}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::Set( UUE2DSpriteAtlasFrame* Frame , FColor InColor , UMaterialInterface* InMaterial )
{
	ComputeVertices( Frame );
	Material												=	InMaterial;
	Color													=	InColor;
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::Set( UUE2DSpriteAtlasFrame* Frame , FColor InColor , FTransform InTransform , UMaterialInterface* InMaterial )
{
	ComputeVertices( Frame , InTransform );

	Material												=	InMaterial;
	Color													=	InColor;
}
//--------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::ComputeVertices( UUE2DSpriteAtlasFrame* InFrame )
{
	InFrame->GetVertices( Vertices );
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::ComputeVertices( UUE2DSpriteAtlasFrame* InFrame , FTransform InTransform )
{
	const TArray< FUE2DSpriteVertex>& TempVertex = InFrame->GetVertices( );

	FVector3d Temp;
	for( FUE2DSpriteVertex Vertex : TempVertex )
	{
		Temp	=	InTransform.TransformVector( (FVector3d)Vertex.Position );
		Vertex.Position = (FVector3f)Temp;

		Vertices.Add( Vertex );
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::Apply( FStaticMeshVertexBuffers& InVertexBuffers )const
{
	uint16 VertexIndex	=	0;
	for(auto ItVert = Vertices.CreateConstIterator(); ItVert; ++ItVert)
	{
		InVertexBuffers.PositionVertexBuffer.VertexPosition(VertexIndex) = ItVert->Position;
		//		VertexBuffers.StaticMeshVertexBuffer.SetVertexTangents(ItVert.GetIndex(), FVector::ForwardVector, TangentY, FVector::UpVector);
		InVertexBuffers.StaticMeshVertexBuffer.SetVertexUV(VertexIndex, 0, ItVert->TexCoord);
		//		VertexBuffers.StaticMeshVertexBuffer.SetVertexUV(ItVert.GetIndex(), 1, ItVert->ColorBlend);
		InVertexBuffers.ColorVertexBuffer.VertexColor( VertexIndex ) = Color;

		VertexIndex ++;
	}

}
//--------------------------------------------------------------------------------------



