#include "UE2DSpriteEditorViewportClient.h"
#include "UE2DSpriteEditor.h"

#include "Sprites/Armature/UE2DSpriteArmature.h"
#include "Components/BillboardComponent.h"

//-------------------------------------------------------------------------------------------
FUE2DSpriteEditorViewportClient::FUE2DSpriteEditorViewportClient( TWeakPtr<FUE2DSpriteEditor> InSpriteEditor , TWeakPtr<class SEditorViewport> InSpriteEditorViewportPtr )
:FEditorViewportClient( nullptr , nullptr , InSpriteEditorViewportPtr ),
SpriteEditorPtr( InSpriteEditor )
{
	SetViewportType( LVT_OrthoXY );

	// use our own empty preview scene instead of default one that preview the world
	PreviewScene	=	&OwnedPreviewScene;
/*
	

	// Get the Atlas to preview
	UUE2DTextureAtlas* Atlas			=	GetAtlasCurrentlyEdited();

	// if the Atlas is valid
	if( Atlas != nullptr )
	{
		UBillboardComponent* Billboard	=	NewObject<UBillboardComponent>( );

		if( Atlas->Textures.Num() > 0 )
		{
			Billboard->SetSprite( (UTexture2D*)Atlas->Textures[ 0 ] );
		}
		
		PreviewScene->AddComponent( Billboard , FTransform::Identity );
	}
	*/
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
UUE2DSprite* FUE2DSpriteEditorViewportClient::GetSpriteCurrentlyEdited() const
{
	return SpriteEditorPtr.Pin()->GetSpriteCurrentlyEdited();
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteEditorViewportClient::DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas )
{

}
//-------------------------------------------------------------------------------------------

