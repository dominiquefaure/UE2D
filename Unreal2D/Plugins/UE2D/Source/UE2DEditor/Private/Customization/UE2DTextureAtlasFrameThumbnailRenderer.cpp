// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "Customization/UE2DTextureAtlasFrameThumbnailRenderer.h"

#include "CanvasItem.h"


//-----------------------------------------------------------------------------------------------
void UUE2DTextureAtlasFrameThumbnailRenderer::Draw( UObject* Object , int32 X , int32 Y , uint32 Width , uint32 Height , FRenderTarget* , FCanvas* Canvas , bool bAdditionalViewFamily )
{
	if( UUE2DTextureAtlasFrame* Frame = Cast<UUE2DTextureAtlasFrame>( Object ) )
	{
		const UTexture2D* SourceTexture = Cast<UTexture2D>( Frame->Texture);


		float TextureWidth	=	Frame->Texture->GetSurfaceWidth();
		float TextureHeight	=	Frame->Texture->GetSurfaceHeight();

		FVector2D UV0;
		FVector2D UV1;
		UV0.X				=	Frame->X / TextureWidth;
		UV0.Y				=	Frame->Y / TextureHeight;

		UV1					=	UV0 + FVector2D( Frame->Width / TextureWidth , Frame->Height / TextureHeight );

		// Use A canvas tile item to draw
		FCanvasTileItem CanvasTile( FVector2D( X , Y ) ,
									SourceTexture->GetResource() ,
									FVector2D( Width , Height ) ,
									UV0 ,
									UV1 ,
									FLinearColor::White );
		CanvasTile.BlendMode = SE_BLEND_Opaque;


		CanvasTile.Draw( Canvas );
	}
}
//-----------------------------------------------------------------------------------------------
