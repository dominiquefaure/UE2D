
#include "UE2DSpriteAtlasEditorFrameList.h"
#include "UE2DSpriteAtlasAssetEditor.h"
#include "Sprites/UE2DSpriteAtlas.h"

#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"

//-------------------------------------------------------------------------------------------
void SUE2DSpriteAtlasEditorFrameList::Construct(const FArguments& InArgs, TSharedPtr<FUE2DSpriteAtlasAssetEditor> InSpriteEditor)
{

	SpriteAtlasEditorPtr	=	InSpriteEditor;


	this->ChildSlot
		[
			SAssignNew( FrameListWidgetPtr , SUE2DSpriteAtlasFrameListWidget )
		];


	UUE2DSpriteAtlas* Atlas	=	SpriteAtlasEditorPtr.Pin()->GetAtlasCurrentlyEdited();
	FrameListWidgetPtr->SetAtlas(Atlas);
}
//-------------------------------------------------------------------------------------------

