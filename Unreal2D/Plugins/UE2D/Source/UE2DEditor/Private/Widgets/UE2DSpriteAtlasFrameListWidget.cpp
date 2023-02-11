
#include "UE2DSpriteAtlasFrameListWidget.h"
#include "Sprites/UE2DSpriteAtlas.h"
#include "Sprites/UE2DSpriteAtlasFrame.h"

#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"

//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasFrameListWidget::Construct(const FArguments& InArgs)
{
	OnSelectedFrameChangedDelegate	=	InArgs._OnSelectedFrameChanged;

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	// Configure filter for asset picker
	FAssetPickerConfig Config;
	Config.Filter.ClassNames.Add(UUE2DSpriteAtlasFrame::StaticClass()->GetFName());
	Config.Filter.ClassPaths.Add( UUE2DSpriteAtlasFrame::StaticClass()->GetClassPathName() );
	Config.InitialAssetViewType			=	EAssetViewType::Tile;
	Config.bAllowDragging				=	false;
	Config.ThumbnailScale				=	0.1;
	Config.bFocusSearchBoxWhenOpened	=	false;
	Config.bShowBottomToolbar			=	false;
	Config.bForceShowEngineContent		=	false;

	Config.OnGetCustomSourceAssets		=	FOnGetCustomSourceAssets::CreateSP(this, &SUE2DSpriteAtlasFrameListWidget::OnGetCustomSourceAssets);
	Config.OnAssetSelected				=	FOnAssetSelected::CreateSP( this , &SUE2DSpriteAtlasFrameListWidget::OnFrameSelected );
	Config.RefreshAssetViewDelegates.Add( &RefreshFrameListDelegate );


//	TSharedPtr<SAssetPicker> AssetPicker;
	TSharedPtr<SWidget> AssetPicker;

	AssetPicker = ContentBrowserModule.Get().CreateAssetPicker( Config );

	this->ChildSlot
		[
			AssetPicker.ToSharedRef()
			
		];

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasFrameListWidget::SetOnSelectedFrameChanged( const FSimpleDelegate& InSelectedFrameChanged )
{

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasFrameListWidget::SetAtlas( UUE2DSpriteAtlas* InAtlas )
{
	SpriteAtlas	=	InAtlas;

	RefreshFrameListDelegate.ExecuteIfBound( true );
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasFrameListWidget::OnGetCustomSourceAssets( const FARFilter& Filter, TArray<FAssetData>& OutAssets ) const
{
	UUE2DSpriteAtlas* Atlas	=	static_cast<UUE2DSpriteAtlas*>( SpriteAtlas.Get() );

	if( Atlas != nullptr )
	{
		for( int i = 0 ; i <  Atlas->Frames.Num() ; i ++ )
		{
			
			OutAssets.Add( Atlas->Frames[ i ] );
		}
	}
	
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasFrameListWidget::OnFrameSelected( const FAssetData& AssetData )
{
	UObject* Asset = nullptr;
	if (AssetData.IsValid())
	{
		Asset = AssetData.GetAsset();
	}

	UUE2DSpriteAtlasFrame* Frame	=	(UUE2DSpriteAtlasFrame*)Asset;

	if( Frame != nullptr )
	{
		UE_LOG(LogTemp, Warning, TEXT("selected frame name = %s") , *(Frame->Name) );


		UUE2DSpriteAtlas* Atlas	=	static_cast<UUE2DSpriteAtlas*>( SpriteAtlas.Get() );

		SelectedFrameIndex	=	Atlas->GetFrameIndex( Frame );
		OnSelectedFrameChangedDelegate.ExecuteIfBound( SelectedFrameIndex.Get() );
	}
}
//-------------------------------------------------------------------------------------------
