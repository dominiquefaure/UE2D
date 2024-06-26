// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "UE2DQuadSpriteIndexBuffer.h"
#include "RenderUtils.h"




//------------------------------------------------------------------------------------------------
void FUE2DQuadSpriteIndexBuffer::InitRHI( FRHICommandListBase& RHICmdList )
{
	if( NumSprites > 0 )
	{

		const uint32 Size = sizeof(uint16) * 6 * NumSprites;
		const uint32 Stride = sizeof(uint16);

		FRHIResourceCreateInfo CreateInfo( TEXT( "FAsQuadSpriteIndexBuffer" ) ) ;
		IndexBufferRHI = RHICmdList.CreateBuffer( Size, BUF_Static | BUF_IndexBuffer, Stride, ERHIAccess::VertexOrIndexBuffer, CreateInfo );

		uint16* Indices = (uint16*)RHICmdList.LockBuffer( IndexBufferRHI, 0, Size, RLM_WriteOnly );

		for (uint32 SpriteIndex = 0; SpriteIndex < NumSprites; ++SpriteIndex)
		{
			Indices[SpriteIndex*6 + 0] = SpriteIndex*4 + 0;
			Indices[SpriteIndex*6 + 1] = SpriteIndex*4 + 3;
			Indices[SpriteIndex*6 + 2] = SpriteIndex*4 + 2;
			Indices[SpriteIndex*6 + 3] = SpriteIndex*4 + 0;
			Indices[SpriteIndex*6 + 4] = SpriteIndex*4 + 1;
			Indices[SpriteIndex*6 + 5] = SpriteIndex*4 + 3;
		}
		RHICmdList.UnlockBuffer( IndexBufferRHI );

	}
}
//------------------------------------------------------------------------------------------------
