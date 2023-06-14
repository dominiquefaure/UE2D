// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "UE2DSceneComponent.h"

#include "Sprites/UE2DSpriteAtlas.h"
#include "Rendering/UE2DSpriteRenderCommandBuilder.h"
#include "UE2DSpriteAtlasComponent.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=(UE2D), editinlinenew , meta=(BlueprintSpawnableComponent) )
class UE2D_API UUE2DSpriteAtlasComponent : public UUE2DSceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUE2DSpriteAtlasComponent();
	~UUE2DSpriteAtlasComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = SpriteAtlas )
	TObjectPtr<class UUE2DSpriteAtlas> Atlas;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , BlueprintSetter= GetFrame , BlueprintSetter = SetFrame , Category = SpriteAtlas )
	int32 FrameIndex;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = SpriteAtlas )
	FColor Color;

	UFUNCTION( BlueprintCallable , BlueprintGetter )
		int32 GetFrame()
	{
		return FrameIndex;
	}

	UFUNCTION( BlueprintCallable  )
	void SetFrame( int32 InFrameIndex );

protected:

	virtual void BeginPlay() override;
	virtual void OnRegister() override;

public:	

	// UActorComponent interface
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	virtual void BuildScene( FUE2DSpriteRenderCommandBuilder* Builder )override;


	// Private Methods
private:

	// update the Mesh to display
	void UpdateMesh( );

	// Private Fields
private:

	bool IsDirty;

};
