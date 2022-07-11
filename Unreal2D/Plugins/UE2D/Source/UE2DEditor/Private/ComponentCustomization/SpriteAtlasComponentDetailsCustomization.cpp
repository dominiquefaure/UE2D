// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpriteAtlasComponentDetailsCustomization.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "IDetailPropertyRow.h"
#include "PropertyCustomizationHelpers.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorStyleSet.h"

#include "UE2DSpriteAtlasComponent.h"
#include "Widgets/UE2DSpriteAtlasFrameListWidget.h"


#define LOCTEXT_NAMESPACE "UE2DComponentCustomization"

//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------------
TSharedRef<IDetailCustomization> FSpriteAtlasComponentDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FSpriteAtlasComponentDetailsCustomization);
}
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
void FSpriteAtlasComponentDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{

	TArray< TWeakObjectPtr<UObject> > CustomizedObjects;
	DetailBuilder.GetObjectsBeingCustomized( CustomizedObjects );

	// customization is not supported for multiple selections
	if( CustomizedObjects.Num() > 1 )
	{
		return;
	}
	CustomizedComponent	=	CastChecked<UUE2DSpriteAtlasComponent>( CustomizedObjects[ 0 ].Get() );

	// Get the SpriteAtlas Categoru
	IDetailCategoryBuilder& SpriteCategory	=	DetailBuilder.EditCategory("SpriteAtlas", FText::GetEmpty(), ECategoryPriority::Important);

	// Get Handle to the different properties needed for customization
	CurrAtlasProperty						=	DetailBuilder.GetProperty( GET_MEMBER_NAME_CHECKED( UUE2DSpriteAtlasComponent , Atlas ) );
	CurrFrameIndexProperty					=	DetailBuilder.GetProperty( GET_MEMBER_NAME_CHECKED( UUE2DSpriteAtlasComponent , FrameIndex ) );
	CurrFrameProperty						=	DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUE2DSpriteAtlasComponent, CurrFrame));

	// remove default appearance and add our custom one
	DetailBuilder.HideProperty( CurrFrameProperty );
	SpriteCategory.AddCustomRow( CurrFrameProperty->GetPropertyDisplayName())
		.NameContent()
		[
			CurrFrameProperty->CreatePropertyNameWidget()
		]
	.ValueContent()
		.MaxDesiredWidth(TOptional<float>())
		[
			SAssignNew( FrameListWidgetPtr , SUE2DSpriteAtlasFrameListWidget )
			.OnSelectedFrameChanged( this , &FSpriteAtlasComponentDetailsCustomization::OnFrameChanged )
		];



	// register a callback when the Atlas selected has changed
	CurrAtlasProperty->SetOnPropertyValueChanged( FSimpleDelegate::CreateSP( this , &FSpriteAtlasComponentDetailsCustomization::OnAtlasChanged ) );

	OnAtlasChanged();
}
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
void FSpriteAtlasComponentDetailsCustomization::OnAtlasChanged()
{
	UObject* PropertyValue = nullptr;
	CurrAtlasProperty->GetValue( PropertyValue );

	FrameListWidgetPtr->SetAtlas( Cast<UUE2DSpriteAtlas>( PropertyValue ) );
}
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
void FSpriteAtlasComponentDetailsCustomization::OnFrameChanged( UUE2DSpriteAtlasFrame* NewFrame)
{
//	CustomizedComponent.Get()->SetFrame( NewFrame );

	UObject* PropertyValue = nullptr;
	CurrAtlasProperty->GetValue( PropertyValue );
	UUE2DSpriteAtlas* Atlas	=	Cast<UUE2DSpriteAtlas>( PropertyValue );
	CurrFrameIndexProperty->SetValue( Atlas->GetFrameIndex( NewFrame) );
}
//------------------------------------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
