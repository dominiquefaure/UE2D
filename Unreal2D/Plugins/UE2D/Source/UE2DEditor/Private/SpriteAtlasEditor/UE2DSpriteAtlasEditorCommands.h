#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EditorStyleSet.h"

class FUE2DSpriteAtlasEditorCommands : public TCommands<FUE2DSpriteAtlasEditorCommands>
{
public:

	/** Constructor */
	FUE2DSpriteAtlasEditorCommands()
		: TCommands<FUE2DSpriteAtlasEditorCommands>("SpriteAtlasEditor", NSLOCTEXT("Contexts", "SpriteAtlasEditor", "SpriteAtlas Editor"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}

	// The Different Commands
	TSharedPtr<FUICommandInfo> ImportAtlas;
	TSharedPtr<FUICommandInfo> AddFrame;
	TSharedPtr<FUICommandInfo> GenerateFrames;


	/** Initialize commands */
	virtual void RegisterCommands() override;

};