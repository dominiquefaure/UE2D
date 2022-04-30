#include "UE2DSpriteAtlasEditorViewport.h"


#include "Widgets/SViewport.h"
#include "Slate/SceneViewport.h"


#define LOCTEXT_NAMESPACE "SUE2DSpriteAtlasEditorViewport"

//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasEditorViewport::Construct( const FArguments& InArgs , const TSharedRef<FUE2DSpriteAtlasAssetEditor>& InSpriteAlasEditor )
{
	AtlasEditorPtr	=	InSpriteAlasEditor;

	SEditorViewport::Construct( SEditorViewport::FArguments() );

/*
	ViewportClient = MakeShareable( new FUE2DSpriteAtlasEditorViewportClient( AtlasEditorPtr , SharedThis( this ) ) );

	Viewport = MakeShareable( new FSceneViewport( ViewportClient.Get() , ViewportWidget ) );

	// The viewport widget needs an interface so it knows what should render
	ViewportWidget->SetViewportInterface( Viewport.ToSharedRef() );
*/
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<FEditorViewportClient> SUE2DSpriteAtlasEditorViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable( new FUE2DSpriteAtlasEditorViewportClient( AtlasEditorPtr , SharedThis( this ) ) );

	return ViewportClient.ToSharedRef();
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
