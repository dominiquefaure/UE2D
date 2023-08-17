// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"

#include "Sprites/UE2DSpriteInstance.h"

#include "UE2DSceneComponent.h"
#include "Rendering/UE2DSpriteRenderCommandBuilder.h"

#include "UE2DSpriteMeshComponent.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=( UE2D ) , editinlinenew , meta=( BlueprintSpawnableComponent ) )
class UE2D_API UUE2DSpriteMeshComponent : public UUE2DSceneComponent
{
	GENERATED_BODY()
	
public:
	
	UUE2DSpriteMeshComponent();
	~UUE2DSpriteMeshComponent();

	// The sprite to use
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = Sprites )
	TObjectPtr<class UUE2DSprite> Sprite;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = TextureAtlas )
	TObjectPtr<class UUE2DTextureAtlas> Atlas;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = TextureAtlas )
	TObjectPtr<class UUE2DTextureAtlas> Atlas2;

// Overrides
protected:

	virtual void BeginPlay() override;
	virtual void OnRegister() override;


#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif


	virtual void BuildScene( FUE2DSpriteRenderCommandBuilder* Builder )override;

private:

	// Set the sprite to display
	void OnSpriteChanged( );

private:

	//TObjectPtr<class UUE2DSpriteInstance> SpriteInstance;

	UUE2DSpriteInstance* SpriteInstance;
};
