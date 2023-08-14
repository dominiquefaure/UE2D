// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DTextureAtlasFactory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "TextureAtlas/UE2DTextureAtlas.h"


//---------------------------------------------------------------------------------------------
UUE2DTextureAtlasFactory::UUE2DTextureAtlasFactory(  )
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UUE2DTextureAtlas::StaticClass();
}
//---------------------------------------------------------------------------------------------
/*
//---------------------------------------------------------------------------------------------
uint32 UUE2DTextureAtlasFactory::GetMenuCategories() const
{
//Let's place this asset in the Blueprints category in the Editor
return EAssetTypeCategories::Blueprint;
}
//---------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------
bool UUE2DTextureAtlasFactory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UUE2DTextureAtlasFactory::FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn )
{
	//Create the editor asset 
	auto NewTextureAtlas							=	NewObject<UUE2DTextureAtlas>(InParent, InClass, InName, Flags);
	return NewTextureAtlas;
}
//---------------------------------------------------------------------------------------------

