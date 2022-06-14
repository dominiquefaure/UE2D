// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "Widgets/UE2DSpriteAtlasFrameListWidget.h"


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

private:

	TSharedPtr<SUE2DSpriteAtlasFrameListWidget> FrameListWidgetPtr;


};
