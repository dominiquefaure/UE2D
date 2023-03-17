// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpriteArmature.generated.h"

class UUE2DSprite;



USTRUCT()
struct FUE2DArmatureBone
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere )
	FString Name;

	UPROPERTY( EditAnywhere )
	int32 ParentBone;

};


USTRUCT()
struct FUE2DArmatureAttachmentSlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY( EditAnywhere )
	FString Name;

	UPROPERTY( EditAnywhere )
	int32 ParentBone;
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

	// the different bones that compose the armature
	UPROPERTY( EditAnywhere )
	TArray<FUE2DArmatureBone> Bones;

	// The different Slots used in the Armature
	UPROPERTY( EditAnywhere )
	TArray<FUE2DArmatureAttachmentSlot> Slots;

	// get the Root Bone
	const FUE2DArmatureBone* GetRoot()const;

	// Get the Childs of the Given Bone
	void GetChilds( uint32 BoneIndex , TArray<FUE2DArmatureBone*> ChildList );

	// Get the Childs of the Given Bone
	TArray<FUE2DArmatureBone*> GetChilds( uint32 BoneIndex );



};
