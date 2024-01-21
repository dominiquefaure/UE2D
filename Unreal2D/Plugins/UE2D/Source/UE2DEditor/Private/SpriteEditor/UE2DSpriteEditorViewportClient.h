// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "UObject/GCObject.h"
#include "UnrealClient.h"


class SUE2DSpriteEditorViewport;
class FUE2DSpriteAssetEditor;
class UUE2DSprite;

class FUE2DSpriteEditorViewportClient : public FEditorViewportClient // , public FGCObject
{
public:

	/** Constructor */
	FUE2DSpriteEditorViewportClient( TWeakPtr<FUE2DSpriteEditor> InSpriteEditor , TWeakPtr<class SEditorViewport> InSpriteEditorViewportPtr );

	virtual void DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas ) override;



private:
	UUE2DSprite* GetSpriteCurrentlyEdited() const;

private:
	
	// Sprite editor that owns this viewport
	TWeakPtr<FUE2DSpriteEditor> SpriteEditorPtr;


	// The preview scene
	FPreviewScene OwnedPreviewScene;



};