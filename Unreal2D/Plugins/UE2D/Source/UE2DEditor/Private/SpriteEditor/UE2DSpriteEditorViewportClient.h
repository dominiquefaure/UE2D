#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "UObject/GCObject.h"
#include "UnrealClient.h"


class SUE2DSpriteEditorViewport;
class FUE2DSpriteAssetEditor;
class UUE2DSpriteArmature;

class FUE2DSpriteEditorViewportClient : public FEditorViewportClient // , public FGCObject
{
public:

	/** Constructor */
	FUE2DSpriteEditorViewportClient( TWeakPtr<FUE2DSpriteEditor> InSpriteEditor , TWeakPtr<class SEditorViewport> InSpriteEditorViewportPtr );

	virtual void DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas ) override;



private:
	UUE2DSpriteArmature* GetArmatureCurrentlyEdited() const;

private:
	
	// Sprite editor that owns this viewport
	TWeakPtr<FUE2DSpriteEditor> SpriteEditorPtr;


	// The preview scene
	FPreviewScene OwnedPreviewScene;



};