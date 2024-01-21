// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Widgets/UE2DTextureAtlasFrameListWidget.h"

#include "Components/UE2DTextureAtlasComponent.h"



class IDetailLayoutBuilder;

//////////////////////////////////////////////////////////////////////////
// FFlipbookComponentDetailsCustomization

class FTextureAtlasComponentDetailsCustomization : public IDetailCustomization
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

	TWeakObjectPtr<UUE2DTextureAtlasComponent> CustomizedComponent;

	TSharedPtr<SUE2DTextureAtlasFrameListWidget> FrameListWidgetPtr;

	TSharedPtr<IPropertyHandle> CurrAtlasProperty;
	TSharedPtr<IPropertyHandle> CurrFrameIndexProperty;

};
