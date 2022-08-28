#include "UE2DSpriteAtlasFrame.h"



//--------------------------------------------------------------------------------------
const TArray<FUE2DSpriteVertex>& UUE2DSpriteAtlasFrame::GetVertices()
{
	if( Vertices.Num() == 0 )
	{
		ComputeVertices();
	}

	return Vertices;
}
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
void UUE2DSpriteAtlasFrame::GetVertices( TArray<FUE2DSpriteVertex>& OutVertices )
{
	if( Vertices.Num() == 0 )
	{
		ComputeVertices();
	}

	for( FUE2DSpriteVertex Vertex : Vertices )
	{
		OutVertices.Add( Vertex );
	}
}
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
void UUE2DSpriteAtlasFrame::ComputeVertices()
{
	float t_x												=	X;
	float t_y												=	Y;
	float t_width											=	Width;
	float t_height											=	Height;
	float t_halfWidth										=	t_width / 2;
	float t_halfHeight										=	t_height / 2;
	float TextureWidth										=	Texture->GetSurfaceWidth();
	float TextureHeight										=	Texture->GetSurfaceHeight();

	float u1												=	0.0f;
	float v1												=	0.0f;
	float u2												=	0.0f;
	float v2												=	0.0f;

	if( TextureWidth > 0 )
	{
		u1													=	(float)t_x / TextureWidth;
		u2													=	(float)( t_x + t_width ) / TextureWidth;
	}

	if( TextureHeight > 0 )
	{
		v1													=	(float)t_y / TextureHeight;
		v2													=	(float)( t_y + t_height ) / TextureHeight;
	}


	FUE2DSpriteVertex Vertex1;
	FUE2DSpriteVertex Vertex2;
	FUE2DSpriteVertex Vertex3;
	FUE2DSpriteVertex Vertex4;


	if( ! Rotated )
	{
		// Standard values
		Vertex1.Position										=	FVector3f( -t_halfWidth , 0 , t_halfHeight );
		Vertex2.Position										=	FVector3f( t_halfWidth , 0 , t_halfHeight );
		Vertex3.Position										=	FVector3f( -t_halfWidth , 0 , -t_halfHeight );
		Vertex4.Position										=	FVector3f( t_halfWidth , 0 , -t_halfHeight );

		Vertex1.TexCoord										=	FVector2f( u1 , v1 );
		Vertex2.TexCoord										=	FVector2f( u2 , v1 );
		Vertex3.TexCoord										=	FVector2f( u1 , v2 );
		Vertex4.TexCoord										=	FVector2f( u2 , v2 );
	}
	else
	{
		// rotated values
		Vertex1.Position										=	FVector3f( -t_halfHeight , 0 , t_halfWidth );
		Vertex2.Position										=	FVector3f( t_halfHeight , 0 , t_halfWidth );
		Vertex3.Position										=	FVector3f( -t_halfHeight , 0 , -t_halfWidth );
		Vertex4.Position										=	FVector3f( t_halfHeight , 0 , -t_halfWidth );

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

