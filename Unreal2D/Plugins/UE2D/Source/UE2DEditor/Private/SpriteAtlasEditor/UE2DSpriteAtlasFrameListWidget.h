
#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

class FUE2DSpriteAtlasAssetEditor;

class SUE2DSpriteAtlasFrameListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUE2DSpriteAtlasFrameListWidget){}
	SLATE_END_ARGS()
public:

	void Construct(const FArguments& InArgs, TSharedPtr<class FUE2DSpriteAtlasAssetEditor> InSpriteEditor);

	// SWidget interface
//	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;
	// End of SWidget interface

//	void SelectAsset(UObject* Asset);

protected:

	void OnGetCustomSourceAssets( const FARFilter& Filter, TArray<FAssetData>& OutAssets ) const;
	void OnFrameSelected( const FAssetData& AssetData );


	// Sprite editor owner
	TWeakPtr<FUE2DSpriteAtlasAssetEditor> SpriteAtlasEditorPtr;

};