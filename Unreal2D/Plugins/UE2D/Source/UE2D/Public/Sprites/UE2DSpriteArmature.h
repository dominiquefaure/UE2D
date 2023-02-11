// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpriteArmature.generated.h"

class UUE2DSprite;


USTRUCT()
struct FUE2DBone
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere  )
	FString Name;

	UPROPERTY( EditAnywhere )
	int32 ParentIndex;


	UPROPERTY( EditAnywhere )
	FTransform LocalTransform;

};


/**
 * 
 */
//UCLASS( BlueprintType , Within=UE2DSprite )
UCLASS( BlueprintType )
class UE2D_API UUE2DSpriteArmature : public UDataAsset
{
	GENERATED_BODY()

public:


	UPROPERTY( EditAnywhere )
	TArray<struct FUE2DBone> Bones;

};
