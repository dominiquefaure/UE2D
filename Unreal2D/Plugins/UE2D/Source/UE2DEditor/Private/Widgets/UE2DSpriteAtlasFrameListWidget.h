
#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"

#include "UE2DSpriteAtlas.h"

class SUE2DSpriteAtlasFrameListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUE2DSpriteAtlasFrameListWidget){}
	SLATE_END_ARGS()
public:

	void Construct( const FArguments& InArgs );

	// SWidget interface
//	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;
	// End of SWidget interface

	/** Set the Atlas this widget will list the Frames*/
	void SetAtlas(UUE2DSpriteAtlas* InAtlas );

protected:

	void OnGetCustomSourceAssets( const FARFilter& Filter, TArray<FAssetData>& OutAssets ) const;
	void OnFrameSelected( const FAssetData& AssetData );


	// the Sprite Atlas that Store all the Frame the Widget will display
	TWeakObjectPtr<UUE2DSpriteAtlas> SpriteAtlas;

};