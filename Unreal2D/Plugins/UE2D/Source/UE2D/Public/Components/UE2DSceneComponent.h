// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Rendering/UE2DSpriteRenderCommandBuilder.h"

#include "UE2DSceneComponent.generated.h"


/**
 * 
 */
UCLASS( ClassGroup=( UE2D ) , editinlinenew , meta=( BlueprintSpawnableComponent ) )
class UE2D_API UUE2DSceneComponent : public UMeshComponent
{
	GENERATED_BODY()
	
public:
	
	UUE2DSceneComponent();
	~UUE2DSceneComponent();



// Overrides
protected:

	virtual void BeginPlay() override;
	virtual void OnRegister() override;

	// UPrimitiveComponent interface
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	virtual FBoxSphereBounds CalcBounds( const FTransform& LocalToWorld ) const override;


	// UActorComponent interface
	virtual void SendRenderDynamicData_Concurrent() override;
	virtual void CreateRenderState_Concurrent( FRegisterComponentContext* Context ) override;


protected:

	virtual void BuildScene( FUE2DSpriteRenderCommandBuilder* Builder );


private:

	// Load the Different Materials that are required
	void InitializeMaterials();

private:

	FUE2DSpriteRenderCommandBuilder	CommandBuilder;

protected:
	TObjectPtr<UMaterialInterface> DefaultSpriteMaterial;

};
