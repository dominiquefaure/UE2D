// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE2DSpriteArmatureBone.generated.h"




UCLASS( transient , NotBlueprintable )
class UE2D_API UUE2DSpriteArmatureBone : public UObject
{
	GENERATED_BODY()

	friend class UUE2DSpriteArmatureInstance;
	friend class UUE2DSpriteInstance;

public:

	FTransform GetGlobalTransform()const;

protected:

	// compute recursively the Global transform
	void ComputeGlobalTransform();

	void AddChild( UUE2DSpriteArmatureBone* Child );


private:

	// the Parent Bone
	UUE2DSpriteArmatureBone* Parent;

	// List of Child bones
	TArray< UUE2DSpriteArmatureBone*> Childs;

	// Local transform apply to this Bone
	FTransform LocalTransform;

	// Global transform of the bone
	FTransform GlobalTransform;

};