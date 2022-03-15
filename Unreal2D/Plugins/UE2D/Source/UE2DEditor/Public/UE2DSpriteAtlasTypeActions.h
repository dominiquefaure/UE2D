// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "UE2DSpriteAtlas.h"




class FUE2DSpriteAtlasTypeActions : public FAssetTypeActions_Base
{
public:
	FUE2DSpriteAtlasTypeActions(EAssetTypeCategories::Type InAssetCategory);

	virtual FColor GetTypeColor() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return FText::FromName(TEXT("SpriteAtlas")); }
	virtual UClass* GetSupportedClass() const override { return UUE2DSpriteAtlas::StaticClass(); }
	virtual uint32 GetCategories() override { return MyAssetCategory; }

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
