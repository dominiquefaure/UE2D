
#pragma once

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/UE2DSpriteAtlasFrameListWidget.h"



class FUE2DSpriteAtlasAssetEditor;

class SUE2DSpriteAtlasEditorFrameList : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUE2DSpriteAtlasEditorFrameList){}
	SLATE_END_ARGS()
public:

	void Construct(const FArguments& InArgs, TSharedPtr<class FUE2DSpriteAtlasAssetEditor> InSpriteEditor);


protected:

	// Sprite editor owner
	TWeakPtr<FUE2DSpriteAtlasAssetEditor> SpriteAtlasEditorPtr;

	TSharedPtr<SUE2DSpriteAtlasFrameListWidget> FrameListWidgetPtr;
};