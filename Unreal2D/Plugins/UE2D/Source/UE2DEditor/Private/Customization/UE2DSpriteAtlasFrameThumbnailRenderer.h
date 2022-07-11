// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThumbnailRendering/DefaultSizedThumbnailRenderer.h"
#include "UE2DSpriteAtlasFrameThumbnailRenderer.generated.h"

/**
 * 
 */
UCLASS()
class UE2DEDITOR_API UUE2DSpriteAtlasFrameThumbnailRenderer : public UDefaultSizedThumbnailRenderer
{
	GENERATED_BODY()
	
	// UThumbnailRenderer interface
	virtual void Draw( UObject* Object , int32 X , int32 Y , uint32 Width , uint32 Height , FRenderTarget* , FCanvas* Canvas , bool bAdditionalViewFamily ) override;
	// End of UThumbnailRenderer interface

};
