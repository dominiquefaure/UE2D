// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteArmatureFactory.h"
#include "AssetTypeCategories.h" //The asset type categories will let us access the various asset categories inside the Editor

#include "Sprites/UE2DSpriteArmature.h"


//---------------------------------------------------------------------------------------------
UUE2DSpriteArmatureFactory::UUE2DSpriteArmatureFactory(  )
{
	bCreateNew												=	true;
	bEditAfterNew											=	true;

	//Configure the class that this factory creates
	SupportedClass											=	UUE2DSpriteArmature::StaticClass();
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
bool UUE2DSpriteArmatureFactory::ShouldShowInNewMenu() const
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UUE2DSpriteArmatureFactory::FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn )
{
	//Create the editor asset 
	auto NewSpriteArmature							=	NewObject<UUE2DSpriteArmature>(InParent, InClass, InName, Flags);
	return NewSpriteArmature;
}
//---------------------------------------------------------------------------------------------

