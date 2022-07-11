// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UE2DSpriteAtlasFrame.generated.h"

class UUE2DSpriteAtlas;

UCLASS(hidecategories=Object, BlueprintType , Within=UE2DSpriteAtlas)
class UE2D_API UUE2DSpriteAtlasFrame : public UObject
{
	friend class UUE2DSpriteAtlas;

	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere )
	FString Name;

	// The texture to use
	UPROPERTY(  EditAnywhere )
	UTexture* Texture;

	// Start X position in the Texture
	UPROPERTY( EditAnywhere)
	int32 X;

	// Start X position in the Texture
	UPROPERTY( EditAnywhere)
	int32 Y;

	// Frame Width
	UPROPERTY( EditAnywhere)
	int32 Width;

	// Frame Height
	UPROPERTY( EditAnywhere)
	int32 Height;

	UPROPERTY( EditAnywhere )
	bool Rotated;

};

