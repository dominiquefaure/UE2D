// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpriteArmatureInstance.generated.h"

class UUE2DSpriteArmatureBone;


UCLASS( transient , NotBlueprintable )
class UE2D_API UUE2DSpriteArmatureInstance : public UObject
{
	GENERATED_BODY()


public:
	UUE2DSpriteArmatureInstance();
	virtual ~UUE2DSpriteArmatureInstance();

	void Init( UUE2DSpriteArmature* Armature );


	int GetBoneCount()const;

	FTransform GetBoneGlobalTransform( int Index );

// Functions
private:


// Members fields
private:

	// the Armature instancied
	TObjectPtr<class UUE2DSpriteArmature> Armature;

	// Runtime version of hte Bones
	TArray<UUE2DSpriteArmatureBone*> Bones;


};