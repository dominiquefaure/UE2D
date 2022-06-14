#include "UE2DSpriteAtlasEditorViewportClient.h"

#include "UE2DSpriteAtlas.h"
#include "Components/BillboardComponent.h"
#include "UE2DSpriteAtlasAssetEditor.h"

//-------------------------------------------------------------------------------------------
FUE2DSpriteAtlasEditorViewportClient::FUE2DSpriteAtlasEditorViewportClient( TWeakPtr<FUE2DSpriteAtlasAssetEditor> InSpriteAtlasEditor , TWeakPtr<class SEditorViewport> InSpriteAtlasEditorViewportPtr )
:FEditorViewportClient( nullptr , nullptr , InSpriteAtlasEditorViewportPtr ),
SpriteAtlasEditorPtr( InSpriteAtlasEditor )
{
	SetViewportType( LVT_OrthoXY );

	// use our own empty preview scene instead of default one that preview the world
	PreviewScene	=	&OwnedPreviewScene;

	

	// Get the Atlas to preview
	UUE2DSpriteAtlas* Atlas			=	GetAtlasCurrentlyEdited();

	// if the Atlas is valid
	if( Atlas != nullptr )
	{
		UBillboardComponent* Billboard	=	NewObject<UBillboardComponent>( );

		Billboard->SetSprite( (UTexture2D*)Atlas->Texture );
		
		PreviewScene->AddComponent( Billboard , FTransform::Identity );
	}
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
UUE2DSpriteAtlas* FUE2DSpriteAtlasEditorViewportClient::GetAtlasCurrentlyEdited() const
{
	return SpriteAtlasEditorPtr.Pin()->GetAtlasCurrentlyEdited();
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasEditorViewportClient::DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas )
{

}
//-------------------------------------------------------------------------------------------

