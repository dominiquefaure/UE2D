// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE2DSpriteAtlasComponent.h"

/*
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
*/

//------------------------------------------------------------------------------------------
UUE2DSpriteAtlasComponent::UUE2DSpriteAtlasComponent()
{
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
UUE2DSpriteAtlasComponent::~UUE2DSpriteAtlasComponent()
{

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
/*
	if( ( Atlas != nullptr ) && ( Atlas->IsValid()) && ( MaterialInstance == nullptr) )
	{
		UMaterialInstanceDynamic* DynamicInstance			=	UMaterialInstanceDynamic::Create( NormalBlendMaterial, GetTransientPackage());
		DynamicInstance->SetTextureParameterValue(FName(TEXT("SpriteTexture")), Atlas->Textures[0]);
		MaterialInstance									=	DynamicInstance;

		SetMaterial( 0 , DynamicInstance  );
	}
*/
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSpriteAtlasComponent::BuildScene( FUE2DSpriteRenderCommandBuilder* Builder )
{
	if( ( Atlas == nullptr ) || ( !Atlas->IsValid() ) )
	{
		return;
	}

	FTransform Transform;
	UUE2DSpriteAtlasFrame* Frame							=	Atlas->GetFrameAt( FrameIndex );

	Builder->AddSprite( Frame , Color , Transform );
}
//------------------------------------------------------------------------------------------
