// Fill out your copyright notice in the Description page of Project Settings.

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