// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RHIDefinitions.h"
#include "UE2DSpriteAtlas.h"
#include "UE2DStructs.h"


struct FColor;



/**
* a Draw commands to send to the render thread
*/
struct FUE2DSpriteDrawCommand
{
	FColor					Color;
	UUE2DSpriteAtlasFrame*	Frame;
	FTransform				Transform;
};