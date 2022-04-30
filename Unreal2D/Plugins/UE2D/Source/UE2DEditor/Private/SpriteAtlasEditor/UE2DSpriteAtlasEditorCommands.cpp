#include "UE2DSpriteAtlasEditorCommands.h"

#define LOCTEXT_NAMESPACE "UE2DSpriteAtlasEditorCommands"

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasEditorCommands::RegisterCommands()
{
	UI_COMMAND(ImportAtlas, "ImportAtlas", "Import the Atlas content from file such as TextureAtlas", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(GenerateFrames, "GenerateFrames", "Generate the  different Frames present in the Texture", EUserInterfaceActionType::Button, FInputChord());
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE
