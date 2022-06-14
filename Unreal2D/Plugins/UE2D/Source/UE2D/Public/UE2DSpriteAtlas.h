// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DSpriteAtlas.generated.h"

class UUE2DSpriteAtlas;

UCLASS(hidecategories=Object, BlueprintType , Within=UE2DSpriteAtlas)
class UE2D_API UUE2DSpriteAtlasFrame : public UObject
{
	friend class UUE2DSpriteAtlas;

	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere )
	FString Name;

	UPROPERTY( EditAnywhere)
	int32 X;

	UPROPERTY( EditAnywhere)
	int32 Y;

	UPROPERTY( EditAnywhere)
	int32 Width;

	UPROPERTY( EditAnywhere)
	int32 Height;

	UPROPERTY( EditAnywhere )
	bool Rotated;

};


/**
 * 
 */
UCLASS(hidecategories=Object, BlueprintType , meta = (DisplayThumbnail = "true") )
class UE2D_API UUE2DSpriteAtlas : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = SimpleSprite, EditAnywhere )
	UTexture* Texture;

	UPROPERTY(Category=Frames, EditAnywhere ,AssetRegistrySearchable, meta = (EditInline) )
	TArray<UUE2DSpriteAtlasFrame*> Frames;


	bool IsValid() { return Texture != nullptr; }

	// Get teh Frame at the given index ( null if invalid index )
	UUE2DSpriteAtlasFrame* GetFrameAt( int32 Index );

	void AddFrame( FString Name , int SrcX , int SrcY , int Width , int Height , bool InRotated );
};
