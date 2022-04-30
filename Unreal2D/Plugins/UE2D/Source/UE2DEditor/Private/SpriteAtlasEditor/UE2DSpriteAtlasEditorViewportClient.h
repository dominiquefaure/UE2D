#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "UObject/GCObject.h"
#include "UnrealClient.h"


class SUE2DSpriteAtlasEditorViewport;
class FUE2DSpriteAtlasAssetEditor;


class FUE2DSpriteAtlasEditorViewportClient : public FEditorViewportClient // , public FGCObject
{
public:

	/** Constructor */
	FUE2DSpriteAtlasEditorViewportClient( TWeakPtr<FUE2DSpriteAtlasAssetEditor> InSpriteAtlasEditor , TWeakPtr<class SEditorViewport> InSpriteAtlasEditorViewportPtr );
//	FUE2DSpriteAtlasEditorViewportClient( TWeakPtr<FUE2DSpriteAtlasAssetEditor> InSpriteAtlasEditor , TWeakPtr<SUE2DSpriteAtlasEditorViewport> InSpriteAtlasEditorViewport );
//	~FUE2DSpriteAtlasEditorViewportClient();

	virtual void DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas ) override;


private:
	
	// The preview scene
	FPreviewScene OwnedPreviewScene;


};