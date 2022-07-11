// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE2DEditorModule.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "UE2DSpriteAtlasTypeActions.h"

#include "UE2DSpriteAtlasComponent.h"
#include "Customization/SpriteAtlasComponentDetailsCustomization.h"
#include "Customization/UE2DSpriteAtlasFrameThumbnailRenderer.h"


#define LOCTEXT_NAMESPACE "FUE2DEditorModule"

void FUE2DEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	EAssetTypeCategories::Type gameAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("UE2D")), FText::FromName(TEXT("UE2D")));

	TSharedPtr<IAssetTypeActions> actionType = MakeShareable(new FUE2DSpriteAtlasTypeActions(gameAssetCategory));

	AssetTools.RegisterAssetTypeActions(actionType.ToSharedRef());

	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FUE2DEditorModule::OnPostEngineInit);



}

void FUE2DEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.


	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		// unregister properties when the module is shutdown
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		
		PropertyModule.UnregisterCustomClassLayout("UUE2DSpriteAtlasComponent");

		PropertyModule.NotifyCustomizationModuleChanged();
	}

}


void FUE2DEditorModule::OnPostEngineInit()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UUE2DSpriteAtlasComponent::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FSpriteAtlasComponentDetailsCustomization::MakeInstance));


	PropertyModule.NotifyCustomizationModuleChanged();


	// Register the thumbnail renderers
	UThumbnailManager::Get().RegisterCustomRenderer( UUE2DSpriteAtlasFrame::StaticClass() , UUE2DSpriteAtlasFrameThumbnailRenderer::StaticClass() );


}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE2DEditorModule, UE2DEditor)