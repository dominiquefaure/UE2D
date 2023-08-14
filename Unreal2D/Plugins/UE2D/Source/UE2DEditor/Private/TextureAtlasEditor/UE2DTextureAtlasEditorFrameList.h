
#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/UE2DTextureAtlasFrameListWidget.h"



class FUE2DTextureAtlasAssetEditor;

class SUE2DTextureAtlasEditorFrameList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUE2DTextureAtlasEditorFrameList){}
	SLATE_END_ARGS()
public:

	void Construct(const FArguments& InArgs, TSharedPtr<class FUE2DTextureAtlasAssetEditor> InSpriteEditor);


protected:

	// Sprite editor owner
	TWeakPtr<FUE2DTextureAtlasAssetEditor> TextureAtlasEditorPtr;

	TSharedPtr<SUE2DTextureAtlasFrameListWidget> FrameListWidgetPtr;
};