// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "UE2DTextureAtlasEditorViewportClient.h"

#include "TextureAtlas/UE2DTextureAtlas.h"
#include "Components/BillboardComponent.h"
#include "UE2DTextureAtlasAssetEditor.h"

//-------------------------------------------------------------------------------------------
FUE2DTextureAtlasEditorViewportClient::FUE2DTextureAtlasEditorViewportClient( TWeakPtr<FUE2DTextureAtlasAssetEditor> InTextureAtlasEditor , TWeakPtr<class SEditorViewport> InTextureAtlasEditorViewportPtr )
:FEditorViewportClient( nullptr , nullptr , InTextureAtlasEditorViewportPtr ),
TextureAtlasEditorPtr( InTextureAtlasEditor )
{
	SetViewportType( LVT_OrthoXY );

	// use our own empty preview scene instead of default one that preview the world
	PreviewScene	=	&OwnedPreviewScene;

	

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
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
UUE2DTextureAtlas* FUE2DTextureAtlasEditorViewportClient::GetAtlasCurrentlyEdited() const
{
	return TextureAtlasEditorPtr.Pin()->GetAtlasCurrentlyEdited();
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasEditorViewportClient::DrawCanvas( FViewport& InViewport , FSceneView& View , FCanvas& Canvas )
{

}
//-------------------------------------------------------------------------------------------

