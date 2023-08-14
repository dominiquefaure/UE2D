#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorStyleSet.h"

class FUE2DTextureAtlasEditorCommands : public TCommands<FUE2DTextureAtlasEditorCommands>
{
public:

	/** Constructor */
	FUE2DTextureAtlasEditorCommands()
		: TCommands<FUE2DTextureAtlasEditorCommands>("TextureAtlasEditor", NSLOCTEXT("Contexts", "TextureAtlasEditor", "TextureAtlas Editor"), NAME_None, FAppStyle::GetAppStyleSetName())
	{
	}

	// The Different Commands
	TSharedPtr<FUICommandInfo> ImportAtlas;
	TSharedPtr<FUICommandInfo> AddFrame;
	TSharedPtr<FUICommandInfo> GenerateFrames;


	/** Initialize commands */
	virtual void RegisterCommands() override;

};