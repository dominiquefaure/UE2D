// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Sprites/UE2DSpriteArmature.h"
#include "UE2DSprite.generated.h"

/**
 * 
 */
UCLASS( hidecategories=Object , BlueprintType , meta = ( DisplayThumbnail = "true" ) )
class UE2D_API UUE2DSprite : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY( EditAnywhere )
	TObjectPtr<UUE2DSpriteArmature> Armature;
};
