// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlasComponent.h"
#include "Rendering/UE2DSpriteAtlasRenderProxy.h"

//------------------------------------------------------------------------------------------
// Sets default values for this component's properties
UUE2DSpriteAtlasComponent::UUE2DSpriteAtlasComponent( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//	bTickInEditor = true;
	SetGenerateOverlapEvents( false );

	bWantsInitializeComponent = true;
	bTickInEditor = true;
	bAutoActivate = true;

	IsDirty													=	true;

	CastShadow												=	false;
	bUseAsOccluder											=	false;
	bCanEverAffectNavigation								=	false;

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// Called when the game starts
void UUE2DSpriteAtlasComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSpriteAtlasComponent::OnRegister()
{
	Super::OnRegister();

	UpdateMesh();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// Called every frame
void UUE2DSpriteAtlasComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSpriteAtlasComponent::SetFrame( int32 InFrameIndex )
{
	if( InFrameIndex != FrameIndex )
	{
		FrameIndex											=	InFrameIndex;
	//	MarkRenderDynamicDataDirty();
	}
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSpriteAtlasComponent::UpdateMesh()
{
	if( IsDirty )
	{
		IsDirty												=	false;

		MarkRenderDynamicDataDirty();
	}

	if( ( Atlas != nullptr ) && ( Atlas->IsValid()) && ( MaterialInstance == nullptr) )
	{
		UMaterialInstanceDynamic* DynamicInstance			=	UMaterialInstanceDynamic::Create( NormalBlendMaterial, GetTransientPackage());
		DynamicInstance->SetTextureParameterValue(FName(TEXT("SpriteTexture")), Atlas->Textures[0]);
		MaterialInstance									=	DynamicInstance;

		SetMaterial( 0 , DynamicInstance  );
	}

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
FPrimitiveSceneProxy* UUE2DSpriteAtlasComponent::CreateSceneProxy()
{
	FUE2DSpriteAtlasRenderSceneProxy* t_proxy				=	nullptr;
	t_proxy													=	new FUE2DSpriteAtlasRenderSceneProxy( this );

	return t_proxy;
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSpriteAtlasComponent::CreateRenderState_Concurrent(FRegisterComponentContext* Context)
{
	Super::CreateRenderState_Concurrent(Context);

	SendRenderDynamicData_Concurrent();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSpriteAtlasComponent::SendRenderDynamicData_Concurrent()
{
	Super::SendRenderDynamicData_Concurrent();

	// Validate the scene proxy have been created
	if( SceneProxy == nullptr )
	{
		return;
	}

	if( (Atlas == nullptr) || (!Atlas->IsValid()) )
	{
		return;
	}

	if(! MaterialInstance->IsValidLowLevelFast() )
	{
		return;
	}


//	FUE2DSpriteRenderCommandBuilder CommandBuilder;
	FTransform Transform;
	UUE2DSpriteAtlasFrame* Frame							=	Atlas->GetFrameAt( FrameIndex );
	UUE2DSpriteAtlasFrame* Frame2							=	Atlas->GetFrameAt( 0 );

	CommandBuilder.Begin();
	CommandBuilder.AddSprite( Frame , Color , Transform );

	Transform.SetTranslation( FVector(80.0f , 0.0f , 100.0f ) );

	CommandBuilder.AddSprite( Frame2 , Color , SecondFrameTransform );

	CommandBuilder.Finish();

	// Cast the Proxy
	FUE2DSpriteAtlasRenderSceneProxy* t_proxy = (FUE2DSpriteAtlasRenderSceneProxy*)SceneProxy;

	ENQUEUE_RENDER_COMMAND( FAsSpriteAtlasRenderSceneProxy_SendDynamicDatas )(
		[t_proxy , Builder=this->CommandBuilder ]( FRHICommandListImmediate& RHICmdList )
		{
			t_proxy->SetDynamicData_RenderThread( Builder.GetCommands() , true );
		}
	);

}
//------------------------------------------------------------------------------------------
