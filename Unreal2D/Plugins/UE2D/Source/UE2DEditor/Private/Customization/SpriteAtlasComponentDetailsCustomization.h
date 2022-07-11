// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Widgets/UE2DSpriteAtlasFrameListWidget.h"

#include "UE2DSpriteAtlasComponent.h"



class IDetailLayoutBuilder;

//////////////////////////////////////////////////////////////////////////
// FFlipbookComponentDetailsCustomization

class FSpriteAtlasComponentDetailsCustomization : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	// IDetailCustomization interface
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;
	// End of IDetailCustomization interface


protected:

	void OnAtlasChanged();

	void OnFrameChanged( int32 NewFrame );

private:

	TWeakObjectPtr<UUE2DSpriteAtlasComponent> CustomizedComponent;

	TSharedPtr<SUE2DSpriteAtlasFrameListWidget> FrameListWidgetPtr;

	TSharedPtr<IPropertyHandle> CurrAtlasProperty;
	TSharedPtr<IPropertyHandle> CurrFrameIndexProperty;

};
