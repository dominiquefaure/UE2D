// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "AssetTypes/UE2DSpriteFactory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Sprites/UE2DSprite.h"


//---------------------------------------------------------------------------------------------
UUE2DSpriteFactory::UUE2DSpriteFactory(  )
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UUE2DSprite::StaticClass();
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
bool UUE2DSpriteFactory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UUE2DSpriteFactory::FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn )
{
	//Create the editor asset 
	auto NewSprite							=	NewObject<UUE2DSprite>(InParent, InClass, InName, Flags);
	return NewSprite;
}
//---------------------------------------------------------------------------------------------

