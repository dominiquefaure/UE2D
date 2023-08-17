// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE2DSpriteMeshComponent.h"

//------------------------------------------------------------------------------------------
UUE2DSpriteMeshComponent::UUE2DSpriteMeshComponent()
{
//	SpriteInstance	=	nullptr;
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
UUE2DSpriteMeshComponent::~UUE2DSpriteMeshComponent()
{
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSpriteMeshComponent::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSpriteMeshComponent::OnRegister()
{
	Super::OnRegister();
	OnSpriteChanged();
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSpriteMeshComponent::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	if( GET_MEMBER_NAME_CHECKED( ThisClass , Sprite ) == PropertyChangedEvent.GetPropertyName() )
	{
		OnSpriteChanged();
	}
}
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
void UUE2DSpriteMeshComponent::OnSpriteChanged( )
{


	SpriteInstance	=	NewObject< UUE2DSpriteInstance>();
	SpriteInstance->SetSprite( Sprite );


	MarkRenderDynamicDataDirty();
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
void UUE2DSpriteMeshComponent::BuildScene( FUE2DSpriteRenderCommandBuilder* Builder )
{
	if( ( Atlas == nullptr ) || ( !Atlas->IsValid() ) )
	{
		return;
	}
	if( ( Atlas2 == nullptr ) || ( !Atlas2->IsValid() ) )
	{
		return;
	}

	SpriteInstance->Draw( Builder , Atlas );
}
//------------------------------------------------------------------------------------------
