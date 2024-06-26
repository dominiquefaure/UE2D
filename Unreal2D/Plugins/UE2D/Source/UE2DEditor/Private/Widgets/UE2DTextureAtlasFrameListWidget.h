// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "ContentBrowserDelegates.h"

#include "TextureAtlas/UE2DTextureAtlas.h"
#include "TextureAtlas/UE2DTextureAtlasFrame.h"

#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"


DECLARE_DELEGATE_OneParam( FOnSelectedFrameChanged , int32 );


class SUE2DTextureAtlasFrameListWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUE2DTextureAtlasFrameListWidget):
	_SelectedFrame( 0 )
	{}

	SLATE_ATTRIBUTE( int32 , SelectedFrame )
	SLATE_EVENT( FOnSelectedFrameChanged , OnSelectedFrameChanged )

	SLATE_END_ARGS()
public:

	void Construct( const FArguments& InArgs );

	// SWidget interface
//	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;
	// End of SWidget interface

	/** Set the Atlas this widget will list the Frames*/
	void SetAtlas(UUE2DTextureAtlas* InAtlas );

	// the Sprite Atlas that Store all the Frame the Widget will display
	UPROPERTY()
	TWeakObjectPtr<UUE2DTextureAtlas> TextureAtlas;


	virtual void SetOnSelectedFrameChanged( const FSimpleDelegate& InSelectedFrameChanged );



protected:

	void OnGetCustomSourceAssets( const FARFilter& Filter, TArray<FAssetData>& OutAssets ) const;
	void OnFrameSelected( const FAssetData& AssetData );

	// Delegate used to force refresh of Frame List
	FRefreshAssetViewDelegate RefreshFrameListDelegate;

	FOnSelectedFrameChanged OnSelectedFrameChangedDelegate;


	TAttribute<int32> SelectedFrameIndex;

};