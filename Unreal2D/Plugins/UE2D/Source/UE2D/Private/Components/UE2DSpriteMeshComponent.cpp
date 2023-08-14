// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE2DSpriteMeshComponent.h"

//------------------------------------------------------------------------------------------
UUE2DSpriteMeshComponent::UUE2DSpriteMeshComponent()
{
	SpriteInstance	=	nullptr;
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
/*
	if( SpriteInstance != nullptr )
	{
		delete SpriteInstance;

		SpriteInstance	=	nullptr;
	}

	if( Sprite )
	{
		SpriteInstance	=	NewObject< UUE2DSpriteInstance>();
		SpriteInstance->Initialize( Sprite );
	}
*/	

/*
	if( ( Atlas != nullptr ) && ( Atlas->IsValid() ) && ( MaterialInstance == nullptr ) )
	{
		UMaterialInstanceDynamic* DynamicInstance			=	UMaterialInstanceDynamic::Create( NormalBlendMaterial , GetTransientPackage() );
		DynamicInstance->SetTextureParameterValue( FName( TEXT( "SpriteTexture" ) ) , Atlas->Textures[ 0 ] );
		MaterialInstance									=	DynamicInstance;

		SetMaterial( 0 , DynamicInstance );
	}
*/
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

	FTransform Transform;
	UUE2DTextureAtlasFrame* Frame							=	Atlas->GetFrameAt( 0 );
	UUE2DTextureAtlasFrame* Frame2							=	Atlas2->GetFrameAt( 0 );

	Builder->AddSprite( Frame , FColor::White , Transform );


	Transform.SetTranslation( FVector( 80.0f , 0.0f , 100.0f ) );
	Builder->AddSprite( Frame2 , FColor::Blue , Transform );


	Builder->AddSprite( Frame , FColor::Yellow , Transform );

}
//------------------------------------------------------------------------------------------
