// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlasTypeActions.h"

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
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);

}
