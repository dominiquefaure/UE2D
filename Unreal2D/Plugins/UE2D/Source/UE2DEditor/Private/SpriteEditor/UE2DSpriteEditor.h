// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"


#include "Sprites/UE2DSprite.h"
#include "Toolkits/AssetEditorToolkit.h"

class SUE2DSpriteEditorViewport;

/**
 * 
 */
class FUE2DSpriteEditor : public FAssetEditorToolkit // , public FGCObject
{
	
public:

	FUE2DSpriteEditor();
	//   virtual ~FUE2DSpriteEditor();

	/**
	* Initializes the editor tool kit.
	*
	* @param InMediaPlayer The UMediaPlayer asset to edit.
	* @param InMode The mode to create the toolkit in.
	* @param InToolkitHost The toolkit host.
	*/
	void Initialize(UUE2DSprite* Sprite, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);






// Interfaces Overrides
public:
	// IToolkit interface
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	// End of IToolkit interface

	// FAssetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
//	virtual FString GetDocumentationLink() const override;
	// End of FAssetEditorToolkit




public:

	// The Armature edited, needed by Viewport
	UUE2DSprite* GetSpriteCurrentlyEdited() const { return Sprite; }



protected:

	// create the different Widgets that will be used in the editor
	void CreateWidgets();

	// Add extra action to the Toolbar
	void ExtendToolbar();

	// Bind the Different Commands that will be handle by this class
	void BindCommands();

	void BuildLayout( const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost );


	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);


// properties
private:

	// pointer to the Sprite to edit
	UUE2DSprite* Sprite;

	/** Property View */
	TSharedPtr<class IDetailsView> DetailsView;

	/** Viewport */
	TSharedPtr<SUE2DSpriteEditorViewport> SpriteViewport;


};
