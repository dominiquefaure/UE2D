// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "Sprites/UE2DSpriteAtlas.h"
#include "UE2DStructs.h"
#include "UE2DSpriteRenderCommand.h"

struct FColor;



/**
* Build a Collection of Draw commands to send to the render thread
*/
class FUE2DSpriteRenderCommandBuilder
{
public:

	FUE2DSpriteRenderCommandBuilder();
	~FUE2DSpriteRenderCommandBuilder();


	void Begin();
	void Finish();

	void AddSprite( UUE2DSpriteAtlasFrame* InFrame , FColor InColor , FTransform InTransform );

	const TArray<FUE2DSpriteRenderCommand>& GetCommands()const;

public:

// Methods
private:

	// Get the index of hte material that represent this Texture
	int GetMaterialIndex( UTexture* InTexture );


private:

	// Collection of Render Commands to send to the Renderer
	TArray<FUE2DSpriteRenderCommand>	Commands;

	uint32								CommandCount;
};