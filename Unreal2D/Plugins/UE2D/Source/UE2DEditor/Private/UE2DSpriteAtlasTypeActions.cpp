// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlasTypeActions.h"
#include "SpriteAtlasEditor/UE2DSpriteAtlasAssetEditor.h"

FUE2DSpriteAtlasTypeActions::FUE2DSpriteAtlasTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FUE2DSpriteAtlasTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

void FUE2DSpriteAtlasTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
//	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto SpriteAtlas = Cast<UUE2DSpriteAtlas>(*ObjIt);

		if (SpriteAtlas != nullptr)
		{
			TSharedRef<FUE2DSpriteAtlasAssetEditor> EditorToolkit = MakeShareable(new FUE2DSpriteAtlasAssetEditor());
			EditorToolkit->Initialize(SpriteAtlas, Mode, EditWithinLevelEditor);
		}
	}

}
