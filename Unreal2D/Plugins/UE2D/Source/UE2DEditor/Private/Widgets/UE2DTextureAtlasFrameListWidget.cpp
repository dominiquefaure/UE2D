
#include "UE2DTextureAtlasFrameListWidget.h"
#include "TextureAtlas/UE2DTextureAtlas.h"
#include "TextureAtlas/UE2DTextureAtlasFrame.h"

#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"

//-------------------------------------------------------------------------------------------
void SUE2DTextureAtlasFrameListWidget::Construct(const FArguments& InArgs)
{
	OnSelectedFrameChangedDelegate	=	InArgs._OnSelectedFrameChanged;

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	// Configure filter for asset picker
	FAssetPickerConfig Config;
	Config.Filter.ClassNames.Add(UUE2DTextureAtlasFrame::StaticClass()->GetFName());
	Config.Filter.ClassPaths.Add( UUE2DTextureAtlasFrame::StaticClass()->GetClassPathName() );
	Config.InitialAssetViewType			=	EAssetViewType::Tile;
	Config.bAllowDragging				=	false;
	Config.ThumbnailScale				=	0.1;
	Config.bFocusSearchBoxWhenOpened	=	false;
	Config.bShowBottomToolbar			=	false;
	Config.bForceShowEngineContent		=	false;

	Config.OnGetCustomSourceAssets		=	FOnGetCustomSourceAssets::CreateSP(this, &SUE2DTextureAtlasFrameListWidget::OnGetCustomSourceAssets);
	Config.OnAssetSelected				=	FOnAssetSelected::CreateSP( this , &SUE2DTextureAtlasFrameListWidget::OnFrameSelected );
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
void SUE2DTextureAtlasFrameListWidget::SetOnSelectedFrameChanged( const FSimpleDelegate& InSelectedFrameChanged )
{

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void SUE2DTextureAtlasFrameListWidget::SetAtlas( UUE2DTextureAtlas* InAtlas )
{
	TextureAtlas	=	InAtlas;

	RefreshFrameListDelegate.ExecuteIfBound( true );
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void SUE2DTextureAtlasFrameListWidget::OnGetCustomSourceAssets( const FARFilter& Filter, TArray<FAssetData>& OutAssets ) const
{
	UUE2DTextureAtlas* Atlas	=	static_cast<UUE2DTextureAtlas*>( TextureAtlas.Get() );

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
void SUE2DTextureAtlasFrameListWidget::OnFrameSelected( const FAssetData& AssetData )
{
	UObject* Asset = nullptr;
	if (AssetData.IsValid())
	{
		Asset = AssetData.GetAsset();
	}

	UUE2DTextureAtlasFrame* Frame	=	(UUE2DTextureAtlasFrame*)Asset;

	if( Frame != nullptr )
	{
		UE_LOG(LogTemp, Warning, TEXT("selected frame name = %s") , *(Frame->Name) );


		UUE2DTextureAtlas* Atlas	=	static_cast<UUE2DTextureAtlas*>( TextureAtlas.Get() );

		SelectedFrameIndex	=	Atlas->GetFrameIndex( Frame );
		OnSelectedFrameChangedDelegate.ExecuteIfBound( SelectedFrameIndex.Get() );
	}
}
//-------------------------------------------------------------------------------------------
