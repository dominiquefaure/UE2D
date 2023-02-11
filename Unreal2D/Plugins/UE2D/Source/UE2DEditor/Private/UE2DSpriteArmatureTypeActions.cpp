// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteArmatureTypeActions.h"
#include "SpriteEditor/UE2DSpriteEditor.h"

FUE2DSpriteArmatureTypeActions::FUE2DSpriteArmatureTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FUE2DSpriteArmatureTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

void FUE2DSpriteArmatureTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
//	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto SpriteAtlas = Cast<UUE2DSpriteArmature>(*ObjIt);

		if (SpriteAtlas != nullptr)
		{
			TSharedRef<FUE2DSpriteEditor> EditorToolkit = MakeShareable(new FUE2DSpriteEditor());
			EditorToolkit->Initialize(SpriteAtlas, Mode, EditWithinLevelEditor);
		}
	}

}
