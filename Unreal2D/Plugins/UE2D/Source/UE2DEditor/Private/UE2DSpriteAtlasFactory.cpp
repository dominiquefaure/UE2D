// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlasFactory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "UE2DSpriteAtlas.h"


//---------------------------------------------------------------------------------------------
UUE2DSpriteAtlasFactory::UUE2DSpriteAtlasFactory(  )
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UUE2DSpriteAtlas::StaticClass();
}
//---------------------------------------------------------------------------------------------
/*
//---------------------------------------------------------------------------------------------
uint32 UUE2DSpriteAtlasFactory::GetMenuCategories() const
{
//Let's place this asset in the Blueprints category in the Editor
return EAssetTypeCategories::Blueprint;
}
//---------------------------------------------------------------------------------------------
*/

//---------------------------------------------------------------------------------------------
bool UUE2DSpriteAtlasFactory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UUE2DSpriteAtlasFactory::FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn )
{
	//Create the editor asset 
	auto NewSpriteAtlas							=	NewObject<UUE2DSpriteAtlas>(InParent, InClass, InName, Flags);
	return NewSpriteAtlas;
}
//---------------------------------------------------------------------------------------------

