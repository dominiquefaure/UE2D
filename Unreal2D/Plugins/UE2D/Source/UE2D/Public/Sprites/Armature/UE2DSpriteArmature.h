// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpriteArmature.generated.h"



USTRUCT()
struct FUE2DArmatureBone
{
	GENERATED_USTRUCT_BODY()

	// name o the Bone, unique in the Armature
	UPROPERTY( EditAnywhere )
	FString Name;

	// Index of the Parent bone
	UPROPERTY( EditAnywhere )
	int32 ParentBone;

	// Bone Default transform
	UPROPERTY( EditAnywhere )
	FTransform DefaultTransform;
};

UENUM()
enum class EArmatureSlotType : uint8
{
	TextureAtlas ,
	SubSprite
};

USTRUCT()
struct FUE2DArmatureSlot
{
	GENERATED_USTRUCT_BODY()

	// unique name of the Attachment
	UPROPERTY( EditAnywhere )
	FString Name;

	// the Bone this Slot is linked to
	UPROPERTY( EditAnywhere )
	int32 BoneIndex;

	UPROPERTY( EditAnywhere )
	EArmatureSlotType AttachmentType;

	// Names of the different attachments that can be used for this Slot. Names are unique per Slot
	UPROPERTY( EditAnywhere )
	TArray<FString> AttachmentNames;

	// Index in the AttachmentName list of the Attachment used by default for this Slot
	UPROPERTY( EditAnywhere )
	uint32 DefaultAttachmentIndex;

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

	// the Different Slots attached to Bones
	UPROPERTY( EditAnywhere )
	TArray< FUE2DArmatureSlot> Slots;


// Functions
public:

	// get the Root Bone
	const FUE2DArmatureBone* GetRoot()const;

	// Get the Childs of the Given Bone
	void GetChildBones( uint32 BoneIndex , TArray<FUE2DArmatureBone*> ChildList );

	// Get the Childs of the Given Bone
	TArray<FUE2DArmatureBone*> GetChildBones( uint32 BoneIndex );




};
