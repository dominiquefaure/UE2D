#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "UObject/GCObject.h"
#include "UnrealClient.h"


class SUE2DTextureAtlasEditorViewport;
class FUE2DTextureAtlasAssetEditor;
class UUE2DTextureAtlas;

class FUE2DTextureAtlasEditorViewportClient : public FEditorViewportClient // , public FGCObject
{
public:

	/** Constructor */
	FUE2DTextureAtlasEditorViewportClient( TWeakPtr<FUE2DTextureAtlasAssetEditor> InTextureAtlasEditor , TWeakPtr<class SEditorViewport> InTextureAtlasEditorViewportPtr );
//	FUE2DTextureAtlasEditorViewportClient( TWeakPtr<FUE2DTextureAtlasAssetEditor> InTextureAtlasEditor , TWeakPtr<SUE2DTextureAtlasEditorViewport> InTextureAtlasEditorViewport );
//	~FUE2DTextureAtlasEditorViewportClient();

	virtual void DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas ) override;



private:
	UUE2DTextureAtlas* GetAtlasCurrentlyEdited() const;

private:
	
	// Sprite editor that owns this viewport
	TWeakPtr<FUE2DTextureAtlasAssetEditor> TextureAtlasEditorPtr;


	// The preview scene
	FPreviewScene OwnedPreviewScene;



};