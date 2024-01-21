// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "UE2DSpriteEditorViewport.h"


#include "Widgets/SViewport.h"
#include "Slate/SceneViewport.h"


#define LOCTEXT_NAMESPACE "SUE2DSpriteEditorViewport"

//-------------------------------------------------------------------------------------------
void SUE2DSpriteEditorViewport::Construct( const FArguments& InArgs , const TSharedRef<FUE2DSpriteEditor>& InSpriteEditor )
{
	SpriteEditorPtr	=	InSpriteEditor;

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
TSharedRef<FEditorViewportClient> SUE2DSpriteEditorViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable( new FUE2DSpriteEditorViewportClient( SpriteEditorPtr , SharedThis( this ) ) );

	return ViewportClient.ToSharedRef();
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
