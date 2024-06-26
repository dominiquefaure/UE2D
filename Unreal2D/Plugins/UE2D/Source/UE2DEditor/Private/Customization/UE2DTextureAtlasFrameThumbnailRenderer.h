// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "UE2DTextureAtlasFrameThumbnailRenderer.generated.h"

/**
 * 
 */
UCLASS()
class UE2DEDITOR_API UUE2DTextureAtlasFrameThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_BODY()
	
	// UThumbnailRenderer interface
	virtual void Draw( UObject* Object , int32 X , int32 Y , uint32 Width , uint32 Height , FRenderTarget* , FCanvas* Canvas , bool bAdditionalViewFamily ) override;
	// End of UThumbnailRenderer interface

};
