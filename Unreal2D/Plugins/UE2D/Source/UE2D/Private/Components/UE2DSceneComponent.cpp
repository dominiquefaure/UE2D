// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE2DSceneComponent.h"
#include "Rendering/UE2DSpriteRenderProxy.h"



//------------------------------------------------------------------------------------------
UUE2DSceneComponent::UUE2DSceneComponent()
{
	InitializeMaterials();

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
UUE2DSceneComponent::~UUE2DSceneComponent()
{

}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::OnRegister()
{
	Super::OnRegister();

	SetMaterial( 0 , DefaultSpriteMaterial );

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
FPrimitiveSceneProxy* UUE2DSceneComponent::CreateSceneProxy()
{
	FUE2DSpriteRenderSceneProxy* t_proxy				=	nullptr;
	t_proxy													=	new FUE2DSpriteRenderSceneProxy( this );

	return t_proxy;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::CreateRenderState_Concurrent( FRegisterComponentContext* Context )
{
	Super::CreateRenderState_Concurrent( Context );

	SendRenderDynamicData_Concurrent();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::SendRenderDynamicData_Concurrent()
{
	Super::SendRenderDynamicData_Concurrent();

	// Validate the scene proxy have been created
	if( SceneProxy == nullptr )
	{
		return;
	}

	CommandBuilder.Begin();
	BuildScene( &CommandBuilder );
	CommandBuilder.Finish();

	// Cast the Proxy
	FUE2DSpriteRenderSceneProxy* t_proxy = (FUE2DSpriteRenderSceneProxy*)SceneProxy;


	ENQUEUE_RENDER_COMMAND( FUE2DSpriteRenderProxy_SendDynamicDatas )(
		[t_proxy , Builder=this->CommandBuilder]( FRHICommandListImmediate& RHICmdList )
		{
			t_proxy->SetDynamicData_RenderThread( Builder.GetCommands() , true );
		}
	);

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::BuildScene( FUE2DSpriteRenderCommandBuilder* Builder )
{

}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::InitializeMaterials()
{

//	static ConstructorHelpers::FObjectFinder<UMaterial> DefaultMaterialRef( TEXT( "/UE2D/StandardSpriteMaterial.StandardSpriteMaterial" ) );
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterialRef( TEXT( "/UE2D/StandardSpriteMaterial" ) );

	DefaultSpriteMaterial						=	DefaultMaterialRef.Object;
/*
	UMaterial* DefaultMaterial					=	CastChecked<UMaterial>( UEditorAssetLibrary::LoadAsset( TEXT("StandardSpriteMaterial") ) );

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>( TEXT( "StaticMesh'/Engine/BasicShapes/Cube.Cube'" ) );
	if( MeshAsset.Object != nullptr )
	{
		Mesh->SetStaticMesh( MeshAsset.Object );
	}
*/
//	/ Script / Engine.Material'/UE2D/StandardSpriteMaterial.StandardSpriteMaterial'
}
//------------------------------------------------------------------------------------------
