// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/UE2DSpriteTypeActions.h"
#include "SpriteEditor/UE2DSpriteEditor.h"

FUE2DSpriteTypeActions::FUE2DSpriteTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FUE2DSpriteTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

void FUE2DSpriteTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto Sprite = Cast<UUE2DSprite>(*ObjIt);

		if ( Sprite != nullptr)
		{
			TSharedRef<FUE2DSpriteEditor> EditorToolkit = MakeShareable(new FUE2DSpriteEditor());
			EditorToolkit->Initialize( Sprite , Mode, EditWithinLevelEditor);
		}
	}

}
