#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "SEditorViewport.h"
#include "UE2DSpriteAtlasEditorViewportClient.h"

class FSceneViewport;
class SScrollBar;
class SViewport;


class SUE2DSpriteAtlasEditorViewport : public SEditorViewport
{
public:

	SLATE_BEGIN_ARGS( SUE2DSpriteAtlasEditorViewport ) { }
	SLATE_END_ARGS()

public:

	/**
	 * Constructs the widget.
	 *
	 * @param InArgs The construction arguments.
	 */
	void Construct( const FArguments& InArgs , const TSharedRef<FUE2DSpriteAtlasAssetEditor>& InAtlasEditor );


	// SEditorViewport interface
//	virtual void BindCommands() override;
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
//	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
//	virtual EVisibility GetTransformToolbarVisibility() const override;
//	virtual void OnFocusViewportToSelection() override;
	// End of SEditorViewport interface



private:

	// Pointer to the Owner Editor
	TWeakPtr<FUE2DSpriteAtlasAssetEditor> AtlasEditorPtr;

	// Level viewport client.
	TSharedPtr<class FUE2DSpriteAtlasEditorViewportClient> ViewportClient;

	// Slate viewport for rendering and IO.
	TSharedPtr<FSceneViewport> Viewport;

	// Viewport widget.
	TSharedPtr<SViewport> ViewportWidget;


};