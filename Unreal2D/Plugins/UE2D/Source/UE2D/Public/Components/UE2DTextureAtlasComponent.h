// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "UE2DSceneComponent.h"

#include "TextureAtlas/UE2DTextureAtlas.h"
#include "Rendering/UE2DSpriteRenderCommandBuilder.h"
#include "UE2DTextureAtlasComponent.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=(UE2D), editinlinenew , meta=(BlueprintSpawnableComponent) )
class UE2D_API UUE2DTextureAtlasComponent : public UUE2DSceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUE2DTextureAtlasComponent();
	~UUE2DTextureAtlasComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = TextureAtlas )
	TObjectPtr<class UUE2DTextureAtlas> Atlas;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , BlueprintSetter= GetFrame , BlueprintSetter = SetFrame , Category = TextureAtlas )
	int32 FrameIndex;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = TextureAtlas )
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
