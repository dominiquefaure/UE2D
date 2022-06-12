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

TSharedRef<IDetailCustomization> FSpriteAtlasComponentDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FSpriteAtlasComponentDetailsCustomization);
}

void FSpriteAtlasComponentDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	// Get the SpriteAtlas Categoru
	IDetailCategoryBuilder& SpriteCategory	=	DetailBuilder.EditCategory("SpriteAtlas", FText::GetEmpty(), ECategoryPriority::Important);

	// Get the PropertyHandle that manage the Current Frame
	TSharedPtr<IPropertyHandle> CurrFrameProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UUE2DSpriteAtlasComponent, CurrFrame));

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
		];

}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
