// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


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

FBoxSphereBounds UUE2DSceneComponent::CalcBounds( const FTransform& LocalToWorld ) const
{
	return FBoxSphereBounds( FVector::ZeroVector , FVector( 128 ) , 128 ).TransformBy( LocalToWorld );
}

//------------------------------------------------------------------------------------------
void UUE2DSceneComponent::CreateRenderState_Concurrent( FRegisterComponentContext* Context )
{
	Super::CreateRenderState_Concurrent( Context );

	FRegisterComponentContext::SendRenderDynamicData( Context , this );

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
		[t_proxy , Builder=this->CommandBuilder]( FRHICommandListBase& RHICmdList )
		{
			t_proxy->SetDynamicData_RenderThread( RHICmdList , Builder.GetCommands() , true );
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
