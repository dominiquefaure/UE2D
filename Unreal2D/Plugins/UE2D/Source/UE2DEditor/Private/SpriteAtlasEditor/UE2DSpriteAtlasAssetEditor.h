// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Editor/PropertyEditor/Public/PropertyEditorDelegates.h"


#include "UE2DSpriteAtlas.h"
#include "Toolkits/AssetEditorToolkit.h"


/**
 * 
 */
class FUE2DSpriteAtlasAssetEditor : public FAssetEditorToolkit // , public FGCObject
{
	
public:

	FUE2DSpriteAtlasAssetEditor();
	//   virtual ~FE2DSpriteAtlasAssetEditor();

	/**
	* Initializes the editor tool kit.
	*
	* @param InMediaPlayer The UMediaPlayer asset to edit.
	* @param InMode The mode to create the toolkit in.
	* @param InToolkitHost The toolkit host.
	*/
	void Initialize(UUE2DSpriteAtlas* Atlas, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);



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







protected:

	// create the different Widgets that will be used in the editor
	void CreateWidgets();

	// Add extra action to the Toolbar
	void ExtendToolbar();

	// Bind the Different Commands that will be handle by this class
	void BindCommands();

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);


	void ImportAtlas();
	void GenerateFrames();
// properties
private:

	// pointer to the SpriteAtlas to edit
	UUE2DSpriteAtlas* SpriteAtlas;

	/** Property View */
	TSharedPtr<class IDetailsView> DetailsView;



};
