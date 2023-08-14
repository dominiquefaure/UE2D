#include "UE2DTextureAtlasEditorViewport.h"


#include "Widgets/SViewport.h"
#include "Slate/SceneViewport.h"


#define LOCTEXT_NAMESPACE "SUE2DTextureAtlasEditorViewport"

//-------------------------------------------------------------------------------------------
void SUE2DTextureAtlasEditorViewport::Construct( const FArguments& InArgs , const TSharedRef<FUE2DTextureAtlasAssetEditor>& InSpriteAlasEditor )
{
	AtlasEditorPtr	=	InSpriteAlasEditor;

	SEditorViewport::Construct( SEditorViewport::FArguments() );

/*
	ViewportClient = MakeShareable( new FUE2DTextureAtlasEditorViewportClient( AtlasEditorPtr , SharedThis( this ) ) );

	Viewport = MakeShareable( new FSceneViewport( ViewportClient.Get() , ViewportWidget ) );

	// The viewport widget needs an interface so it knows what should render
	ViewportWidget->SetViewportInterface( Viewport.ToSharedRef() );
*/
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<FEditorViewportClient> SUE2DTextureAtlasEditorViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable( new FUE2DTextureAtlasEditorViewportClient( AtlasEditorPtr , SharedThis( this ) ) );

	return ViewportClient.ToSharedRef();
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
