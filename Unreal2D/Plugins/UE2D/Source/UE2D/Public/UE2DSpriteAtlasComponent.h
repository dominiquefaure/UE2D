// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "UE2DSpriteAtlas.h"
#include "UE2DSpriteAtlasComponent.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=(UE2D), meta=(BlueprintSpawnableComponent) )
class UE2D_API UUE2DSpriteAtlasComponent : public UMeshComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UUE2DSpriteAtlasComponent();

	UPROPERTY(Category = Material, EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* NormalBlendMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = SpriteAtlas )
	TObjectPtr<class UUE2DSpriteAtlas> Atlas;

	UPROPERTY(Category = SpriteAtlas, EditAnywhere, BlueprintReadWrite, Interp)
	int32 FrameIndex;

	UPROPERTY(EditAnywhere, Category=SpriteAtlas)
	TObjectPtr<class UUE2DSpriteAtlasFrame> CurrFrame;


protected:

	virtual void BeginPlay() override;
	virtual void OnRegister() override;

public:	

	// UActorComponent interface
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SendRenderDynamicData_Concurrent() override;
	virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;

	// UPrimitiveComponent interface
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;


	// Private Methods
private:

	// update the Mesh to display
	void UpdateMesh( );

	// Private Fields
private:

	bool IsDirty;

	// Instance of the Material to avoid create it every tick in the record
	UMaterialInterface* MaterialInstance;

};
