// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DSpriteAtlas.generated.h"

class UUE2DSpriteAtlas;

USTRUCT()
struct FUE2DSpriteAtlasFrame
{
	friend class UUE2DSpriteAtlas;

	GENERATED_USTRUCT_BODY()


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

	// Position of the Pivot Point within the region
	FVector2D PivotPoint;

};


/**
 * 
 */
UCLASS()
class UE2D_API UUE2DSpriteAtlas : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Category = SimpleSprite, EditAnywhere )
	UTexture* Texture;

	UPROPERTY(Category=Frames, EditAnywhere)
	TArray<FUE2DSpriteAtlasFrame> Frames;


	bool IsValid() { return Texture != nullptr; }

	// Get teh Frame at the given index ( null if invalid index )
	FUE2DSpriteAtlasFrame* GetFrameAt( int32 Index );


};
