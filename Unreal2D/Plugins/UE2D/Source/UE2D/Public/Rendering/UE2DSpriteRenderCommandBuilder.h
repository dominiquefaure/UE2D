// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "TextureAtlas/UE2DTextureAtlas.h"
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

	void AddSprite( UUE2DTextureAtlasFrame* InFrame , FColor InColor , FTransform InTransform );

	const TArray<FUE2DSpriteRenderCommand>& GetCommands()const;


private:

	// Collection of Render Commands to send to the Renderer
	TArray<FUE2DSpriteRenderCommand>	Commands;

	uint32								CommandCount;
};