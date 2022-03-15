// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE2DEditorModule.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "UE2DSpriteAtlasTypeActions.h"


#define LOCTEXT_NAMESPACE "FUE2DEditorModule"

void FUE2DEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	EAssetTypeCategories::Type gameAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("UE2D")), FText::FromName(TEXT("UE2D")));

	TSharedPtr<IAssetTypeActions> actionType = MakeShareable(new FUE2DSpriteAtlasTypeActions(gameAssetCategory));

	AssetTools.RegisterAssetTypeActions(actionType.ToSharedRef());

}

void FUE2DEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE2DEditorModule, UE2DEditor)