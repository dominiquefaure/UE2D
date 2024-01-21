// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE2DEditorModule.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "AssetTypes/UE2DTextureAtlasTypeActions.h"
#include "AssetTypes/UE2DSpriteTypeActions.h"

#include "Components/UE2DTextureAtlasComponent.h"
#include "Customization/UE2DTextureAtlasComponentDetailsCustomization.h"
#include "Customization/UE2DTextureAtlasFrameThumbnailRenderer.h"


#define LOCTEXT_NAMESPACE "FUE2DEditorModule"

void FUE2DEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	EAssetTypeCategories::Type gameAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("UE2D")), FText::FromName(TEXT("UE2D")));

	// Register Sprite Atlas Actions
	TSharedPtr<IAssetTypeActions> TextureAtlasActionType = MakeShareable( new FUE2DTextureAtlasTypeActions( gameAssetCategory ) );
	AssetTools.RegisterAssetTypeActions( TextureAtlasActionType.ToSharedRef() );

	// Register Sprite Armature Actions
	TSharedPtr<FUE2DSpriteTypeActions> SpriteArmatureActionType = MakeShareable(new FUE2DSpriteTypeActions(gameAssetCategory));
	AssetTools.RegisterAssetTypeActions( SpriteArmatureActionType.ToSharedRef());

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
		
		PropertyModule.UnregisterCustomClassLayout("UUE2DTextureAtlasComponent");

		PropertyModule.NotifyCustomizationModuleChanged();
	}

}


void FUE2DEditorModule::OnPostEngineInit()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UUE2DTextureAtlasComponent::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FTextureAtlasComponentDetailsCustomization::MakeInstance));


	PropertyModule.NotifyCustomizationModuleChanged();


	// Register the thumbnail renderers
	UThumbnailManager::Get().RegisterCustomRenderer( UUE2DTextureAtlasFrame::StaticClass() , UUE2DTextureAtlasFrameThumbnailRenderer::StaticClass() );


}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE2DEditorModule, UE2DEditor)