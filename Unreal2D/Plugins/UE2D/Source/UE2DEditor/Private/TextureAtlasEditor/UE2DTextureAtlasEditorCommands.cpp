// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "UE2DTextureAtlasEditorCommands.h"

#define LOCTEXT_NAMESPACE "UE2DTextureAtlasEditorCommands"

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasEditorCommands::RegisterCommands()
{
	UI_COMMAND(ImportAtlas, "ImportAtlas", "Import the Atlas content from file such as TextureAtlas", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(GenerateFrames, "GenerateFrames", "Generate the  different Frames present in the Texture", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AddFrame, "AddFrame", "Add a new Empty frame", EUserInterfaceActionType::Button, FInputChord());
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
