// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"



/**
 * Custom Dynamic Index Buffer
 */
class FUE2DQuadSpriteIndexBuffer : public FIndexBuffer
{
public:
	FUE2DQuadSpriteIndexBuffer()
		: NumSprites(1)
	{
	}
	virtual void InitRHI( FRHICommandListBase& RHICmdList ) override;

	uint32 NumSprites;
};