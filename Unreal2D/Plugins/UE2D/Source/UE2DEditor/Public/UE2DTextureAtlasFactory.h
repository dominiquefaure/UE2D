// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UE2DTextureAtlasFactory.generated.h"

/**
 * 
 */
UCLASS()
class UE2DEDITOR_API UUE2DTextureAtlasFactory : public UFactory
{
	GENERATED_BODY()
	
public:

	UUE2DTextureAtlasFactory();

	// Allow to place the asset into dedicated category when try to add new asset
	//	virtual uint32 GetMenuCategories() const override;

	// Creates the asset inside the UE4 Editor
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	virtual bool ShouldShowInNewMenu() const override;


};
