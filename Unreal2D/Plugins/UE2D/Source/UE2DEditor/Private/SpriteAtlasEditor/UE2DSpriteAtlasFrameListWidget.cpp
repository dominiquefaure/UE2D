
#include "UE2DSpriteAtlasFrameListWidget.h"
#include "UE2DSpriteAtlas.h"
#include "UE2DSpriteAtlasAssetEditor.h"

#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"

void SUE2DSpriteAtlasFrameListWidget::Construct(const FArguments& InArgs, TSharedPtr<FUE2DSpriteAtlasAssetEditor> InSpriteEditor)
{

	SpriteAtlasEditorPtr	=	InSpriteEditor;

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	// Configure filter for asset picker
	FAssetPickerConfig Config;
	Config.Filter.ClassNames.Add(UUE2DSpriteAtlasFrame::StaticClass()->GetFName());
	Config.InitialAssetViewType		=	EAssetViewType::Tile;
	Config.OnGetCustomSourceAssets	=	FOnGetCustomSourceAssets::CreateSP(this, &SUE2DSpriteAtlasFrameListWidget::OnGetCustomSourceAssets);
	Config.OnAssetSelected			=	FOnAssetSelected::CreateSP( this , &SUE2DSpriteAtlasFrameListWidget::OnFrameSelected );


	this->ChildSlot
		[
			ContentBrowserModule.Get().CreateAssetPicker(Config)
		];

}

void SUE2DSpriteAtlasFrameListWidget::OnGetCustomSourceAssets( const FARFilter& Filter, TArray<FAssetData>& OutAssets ) const
{
	UUE2DSpriteAtlas* Atlas	=	SpriteAtlasEditorPtr.Pin()->GetAtlasCurrentlyEdited();

	for( int i = 0 ; i <  Atlas->Frames.Num() ; i ++ )
	{
		OutAssets.Add( Atlas->Frames[ i ] );
	}

}

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
	}
}