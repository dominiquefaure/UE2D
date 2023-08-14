#include "Rendering/UE2DSpriteRenderCommand.h"
#include "TextureAtlas/UE2DTextureAtlas.h"

//------------------------------------------------------------------------------
FUE2DSpriteRenderCommand::FUE2DSpriteRenderCommand()
{

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
FUE2DSpriteRenderCommand::~FUE2DSpriteRenderCommand()
{

}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void FUE2DSpriteRenderCommand::Set( UUE2DTextureAtlasFrame* InFrame , FTransform InTransform , FColor InColor , UTexture* InTexture , float DeltaY )
{
	Texture			=	InTexture;
	Color			=	InColor;

	ComputeVertices( InFrame  , InTransform , DeltaY );
}
//------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderCommand::ComputeVertices( UUE2DTextureAtlasFrame* InFrame , FTransform InTransform , float DeltaY )
{
	const TArray< FUE2DSpriteVertex>& TempVertex = InFrame->GetVertices();

	FVector3d Temp;
	for( FUE2DSpriteVertex Vertex : TempVertex )
	{
		Temp				=	InTransform.TransformPosition( (FVector3d)Vertex.Position );
		Vertex.Position		=	(FVector3f)Temp;
		Vertex.Position.Y	+=	DeltaY;

		Vertices.Add( Vertex );
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void FUE2DSpriteRenderCommand::WriteToVertexBuffer( FStaticMeshVertexBuffers& InVertexBuffers , uint32& VertexIndex )const
{
	for( auto ItVert = Vertices.CreateConstIterator(); ItVert; ++ItVert )
	{
		InVertexBuffers.PositionVertexBuffer.VertexPosition( VertexIndex ) = ItVert->Position;
		//		VertexBuffers.StaticMeshVertexBuffer.SetVertexTangents(ItVert.GetIndex(), FVector::ForwardVector, TangentY, FVector::UpVector);
		InVertexBuffers.StaticMeshVertexBuffer.SetVertexUV( VertexIndex , 0 , ItVert->TexCoord );
		//		VertexBuffers.StaticMeshVertexBuffer.SetVertexUV(ItVert.GetIndex(), 1, ItVert->ColorBlend);
		InVertexBuffers.ColorVertexBuffer.VertexColor( VertexIndex ) = Color;

		VertexIndex ++;
	}

}
//--------------------------------------------------------------------------------------
