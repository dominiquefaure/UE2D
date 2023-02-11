// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DSpriteAtlas.generated.h"

class UUE2DSpriteAtlasFrame;


/**
 * 
 */
UCLASS(hidecategories=Object, BlueprintType , meta = (DisplayThumbnail = "true") )
class UE2D_API UUE2DSpriteAtlas : public UObject
{
	GENERATED_BODY()

public:

	// The different Textures required by this Atlas
	UPROPERTY(Category = SimpleSprite, EditAnywhere )
	TArray<UTexture*> Textures;

	// The different Frames of this Atlas
	UPROPERTY(Category=Frames, EditAnywhere ,AssetRegistrySearchable, meta = (EditInline) )
	TArray<UUE2DSpriteAtlasFrame*> Frames;


	bool IsValid() { return Textures.Num() >0; }

	// Get the Frame at the given index ( null if invalid index )
	UUE2DSpriteAtlasFrame* GetFrameAt( int32 Index );

	/* Get the index of the given frame
	*/
	int32 GetFrameIndex( UUE2DSpriteAtlasFrame* InFrame );


	void AddFrame( UTexture2D* InTexture , FString Name , int SrcX , int SrcY , int Width , int Height , bool InRotated );
	void AddFrame( FString Name , int TextureIndex , int SrcX , int SrcY , int Width , int Height , bool InRotated );
};
