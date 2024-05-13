// Copyright 2022-2024 Dominique Faure. All Rights Reserved.


#include "Components/UE2DTextureAtlasComponent.h"

/*
//------------------------------------------------------------------------------------------
// Sets default values for this component's properties
UUE2DTextureAtlasComponent::UUE2DTextureAtlasComponent( const FObjectInitializer& ObjectInitializer )
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
UUE2DTextureAtlasComponent::UUE2DTextureAtlasComponent()
{
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
UUE2DTextureAtlasComponent::~UUE2DTextureAtlasComponent()
{

}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
// Called when the game starts
void UUE2DTextureAtlasComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DTextureAtlasComponent::OnRegister()
{
	Super::OnRegister();

	UpdateMesh();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// Called every frame
void UUE2DTextureAtlasComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DTextureAtlasComponent::SetFrame( int32 InFrameIndex )
{
	if( InFrameIndex != FrameIndex )
	{
		FrameIndex											=	InFrameIndex;
		MarkRenderDynamicDataDirty();
	}
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DTextureAtlasComponent::UpdateMesh()
{
	if( IsDirty )
	{
		IsDirty												=	false;

		MarkRenderDynamicDataDirty();
	}
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DTextureAtlasComponent::BuildScene( FUE2DSpriteRenderCommandBuilder* Builder )
{
	if( ( Atlas == nullptr ) || ( !Atlas->IsValid() ) )
	{
		return;
	}

	FTransform Transform;
	UUE2DTextureAtlasFrame* Frame							=	Atlas->GetFrameAt( FrameIndex );

	Builder->AddSprite( Frame , Color , Transform );
}
//------------------------------------------------------------------------------------------
