// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE2DSceneComponent.h"
#include "Rendering/UE2DSpriteRenderProxy.h"

//------------------------------------------------------------------------------------------
UUE2DSceneComponent::UUE2DSceneComponent()
{
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
/*
	RenderBuilder.Begin();
	BuildScene( &RenderBuilder );
	RenderBuilder.Finish();
*/

	CommandBuilder.Begin();
	BuildScene( &CommandBuilder );
	CommandBuilder.Finish();

	// Cast the Proxy
	FUE2DSpriteRenderSceneProxy* t_proxy = (FUE2DSpriteRenderSceneProxy*)SceneProxy;

/*	ENQUEUE_RENDER_COMMAND(FUE2DSpriteRenderProxy_SendDynamicDatas)(
		[t_proxy , Builder=this->RenderBuilder]( FRHICommandListImmediate& RHICmdList )
		{
			t_proxy->SetDynamicData_RenderThread( Builder );
		}
	);
*/

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
