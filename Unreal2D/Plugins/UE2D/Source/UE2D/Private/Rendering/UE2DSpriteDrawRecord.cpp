#include "UE2DSpriteDrawRecord.h"


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
void FUE2DSpriteDrawRecord::Set( UUE2DSpriteAtlas* Atlas, uint32 FrameIndex, UMaterialInterface* InMaterial )
{
	if( Atlas == nullptr )
	{
		return;
	}

	FUE2DSpriteAtlasFrame* Frame							=	Atlas->GetFrameAt( FrameIndex );

	if( Frame == nullptr )
	{
		return;
	}

	ComputeVertices( Atlas , Frame );

	Material												=	InMaterial;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void FUE2DSpriteDrawRecord::ComputeVertices( UUE2DSpriteAtlas* Atlas, FUE2DSpriteAtlasFrame* InFrame )
{
	float t_x			=	InFrame->X;
	float t_y			=	InFrame->Y;
	float t_width		=	InFrame->Width;
	float t_height		=	InFrame->Height;
	bool Rotated		=	InFrame->Rotated;

	float t_halfWidth	=	t_width /2;
	float t_halfHeight	=	t_height/2;


	float TextureWidth	=	Atlas->Texture->GetSurfaceWidth();
	float TextureHeight	=	Atlas->Texture->GetSurfaceHeight();

	float u1												=	0.0f;
	float v1												=	0.0f;
	float u2												=	0.0f;
	float v2												=	0.0f;

	if( TextureWidth > 0 )
	{
		u1													=	(float)t_x / TextureWidth;
		u2													=	(float)(t_x + t_width ) / TextureWidth;
	}

	if( TextureHeight > 0 )
	{
		v1													=	(float)t_y / TextureHeight;
		v2													=	(float)(t_y + t_height ) / TextureHeight;
	}



	FUE2DSpriteVertex Vertex1;
	FUE2DSpriteVertex Vertex2;
	FUE2DSpriteVertex Vertex3;
	FUE2DSpriteVertex Vertex4;


	if(! InFrame->Rotated )
	{
		// Standard values
		Vertex1.Position										=	FVector( -t_halfWidth , 0 , t_halfHeight );
		Vertex2.Position										=	FVector( t_halfWidth , 0 , t_halfHeight );
		Vertex3.Position										=	FVector( -t_halfWidth , 0 , -t_halfHeight );
		Vertex4.Position										=	FVector( t_halfWidth , 0 , -t_halfHeight );

		Vertex1.TexCoord										=	FVector2f( u1 , v1 );
		Vertex2.TexCoord										=	FVector2f( u2 , v1 );
		Vertex3.TexCoord										=	FVector2f( u1 , v2 );
		Vertex4.TexCoord										=	FVector2f( u2 , v2 );



	}
	else
	{
		// rotated values
		Vertex1.Position										=	FVector( -t_halfHeight , 0 , t_halfWidth );
		Vertex2.Position										=	FVector( t_halfHeight , 0 , t_halfWidth );
		Vertex3.Position										=	FVector( -t_halfHeight , 0 , -t_halfWidth );
		Vertex4.Position										=	FVector( t_halfHeight , 0 , -t_halfWidth );

		Vertex1.TexCoord										=	FVector2f( u1 , v2 );
		Vertex2.TexCoord										=	FVector2f( u1 , v1 );
		Vertex3.TexCoord										=	FVector2f( u2 , v2 );
		Vertex4.TexCoord										=	FVector2f( u2 , v1 );

	}

	Vertices.Add( Vertex1 );
	Vertices.Add( Vertex2 );
	Vertices.Add( Vertex3 );
	Vertices.Add( Vertex4 );
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
		//		VertexBuffers.ColorVertexBuffer.VertexColor(ItVert.GetIndex()) = ItVert->Color;

		VertexIndex ++;
	}

}
//--------------------------------------------------------------------------------------
