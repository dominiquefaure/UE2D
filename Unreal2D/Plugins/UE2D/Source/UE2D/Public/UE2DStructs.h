
#pragma once

#include "CoreMinimal.h"


/*
* Definition of a Vertex for an AsSprite
*/
struct UE2D_API FUE2DSpriteVertex
{
	FVector3f	Position;
	FVector2f	TexCoord;
	FColor		Color;
};


/*
* Contain the necessary parameters to perform a draw call
*/
struct FUE2DSpriteRenderBatch
{
	FUE2DSpriteRenderBatch()
	{
		MaterialProxy	=	nullptr;
	}

	// The Material to use for the Whole Batch
	FMaterialRenderProxy* MaterialProxy;

	// First Index in the IndexBuffer
	uint32 FirstIndex;
	uint32 MaxIndex;

	// Number of primitive to draw
	uint32 NumPrimitives;
	uint32 MinVertexIndex;
	uint32 MaxVertexIndex;
};
