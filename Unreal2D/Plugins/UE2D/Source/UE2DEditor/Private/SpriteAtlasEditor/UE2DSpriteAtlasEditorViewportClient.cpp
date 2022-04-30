#include "UE2DSpriteAtlasEditorViewportClient.h"

//-------------------------------------------------------------------------------------------
FUE2DSpriteAtlasEditorViewportClient::FUE2DSpriteAtlasEditorViewportClient( TWeakPtr<FUE2DSpriteAtlasAssetEditor> InSpriteAtlasEditor , TWeakPtr<class SEditorViewport> InSpriteAtlasEditorViewportPtr )
:FEditorViewportClient( nullptr , nullptr , InSpriteAtlasEditorViewportPtr )
{
	SetViewportType( LVT_OrthoXY );

	// use our own empty preview scene insteqd of defqult one thqt preview the world
	PreviewScene	=	&OwnedPreviewScene;

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasEditorViewportClient::DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas )
{

}
//-------------------------------------------------------------------------------------------

