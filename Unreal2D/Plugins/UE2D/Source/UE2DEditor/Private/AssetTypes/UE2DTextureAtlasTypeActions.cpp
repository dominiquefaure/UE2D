// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/UE2DTextureAtlasTypeActions.h"
#include "TextureAtlasEditor/UE2DTextureAtlasAssetEditor.h"

FUE2DTextureAtlasTypeActions::FUE2DTextureAtlasTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FUE2DTextureAtlasTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

void FUE2DTextureAtlasTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
//	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto TextureAtlas = Cast<UUE2DTextureAtlas>(*ObjIt);

		if (TextureAtlas != nullptr)
		{
			TSharedRef<FUE2DTextureAtlasAssetEditor> EditorToolkit = MakeShareable(new FUE2DTextureAtlasAssetEditor());
			EditorToolkit->Initialize(TextureAtlas, Mode, EditWithinLevelEditor);
		}
	}

}
