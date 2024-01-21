// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "UE2DTextureAtlasEditorFrameList.h"
#include "UE2DTextureAtlasAssetEditor.h"
#include "TextureAtlas/UE2DTextureAtlas.h"

#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"

//-------------------------------------------------------------------------------------------
void SUE2DTextureAtlasEditorFrameList::Construct(const FArguments& InArgs, TSharedPtr<FUE2DTextureAtlasAssetEditor> InSpriteEditor)
{

	TextureAtlasEditorPtr	=	InSpriteEditor;


	this->ChildSlot
		[
			SAssignNew( FrameListWidgetPtr , SUE2DTextureAtlasFrameListWidget )
		];


	UUE2DTextureAtlas* Atlas	=	TextureAtlasEditorPtr.Pin()->GetAtlasCurrentlyEdited();
	FrameListWidgetPtr->SetAtlas(Atlas);
}
//-------------------------------------------------------------------------------------------

