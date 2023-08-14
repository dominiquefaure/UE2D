// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DTextureAtlasAssetEditor.h"

#include "DesktopPlatformModule.h"
#include "EditorDirectories.h"

#include "UE2DTextureAtlasEditorCommands.h"
#include "UE2DTextureAtlasEditorViewport.h"
#include "UE2DTextureAtlasEditorFrameList.h"
#include <importers/SpineImporters/SpineAtlas.h>


#define LOCTEXT_NAMESPACE "TextureAtlasEditor"

namespace UE2DTextureAtlasEditorToolkitTabs
{
	static const FName AppIdentifier("TextureAtlasEditorApp");
	static const FName ViewportID("Viewport");
	static const FName DetailsID("Details");
	static const FName FrameListID("FrameList");
}



//-------------------------------------------------------------------------------------------
FUE2DTextureAtlasAssetEditor::FUE2DTextureAtlasAssetEditor()
{

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
FText FUE2DTextureAtlasAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "TextureAtlas Editor");
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FName FUE2DTextureAtlasAssetEditor::GetToolkitFName() const
{
	return FName("TextureAtlasEditor");
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FLinearColor FUE2DTextureAtlasAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FString FUE2DTextureAtlasAssetEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("TextureAtlasEditor");
}
//-------------------------------------------------------------------------------------------



///////////////////////////////
// Editor Initialization

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::Initialize( UUE2DTextureAtlas* Atlas, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost )
{
	if( Atlas == nullptr)
	{
		return;
	}

	TextureAtlas	=	Atlas;


	// Register the Commands before linking it in any of the widgets / menu
	FUE2DTextureAtlasEditorCommands::Register();
	BindCommands();
	CreateWidgets();

	BuildLayout( InMode , InToolkitHost );

	ExtendToolbar();
	RegenerateMenusAndToolbars();

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::ExtendToolbar()
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& ToolbarBuilder)
			{
				ToolbarBuilder.BeginSection("Importers");
				{
					ToolbarBuilder.AddToolBarButton(FUE2DTextureAtlasEditorCommands::Get().ImportAtlas);
				}
				ToolbarBuilder.EndSection();
			})
	);
	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateLambda([](FToolBarBuilder& ToolbarBuilder)
			{
				ToolbarBuilder.BeginSection("AddFrame");
				{
					ToolbarBuilder.AddToolBarButton(FUE2DTextureAtlasEditorCommands::Get().AddFrame);
				}
				ToolbarBuilder.EndSection();
			})
	);

	AddToolbarExtender(ToolbarExtender);


}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::BindCommands()
{
	FUE2DTextureAtlasEditorCommands::Register();
	const FUE2DTextureAtlasEditorCommands& Commands = FUE2DTextureAtlasEditorCommands::Get();

	const TSharedRef<FUICommandList>& CommandList = GetToolkitCommands();

	CommandList->MapAction(
		Commands.ImportAtlas,
		FExecuteAction::CreateSP(this, &FUE2DTextureAtlasAssetEditor::ImportAtlas));

	CommandList->MapAction(
		Commands.AddFrame,
		FExecuteAction::CreateSP(this, &FUE2DTextureAtlasAssetEditor::AddFrame));

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::CreateWidgets()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyModule.CreateDetailView(Args);

	DetailsView->SetObject(TextureAtlas);


	TSharedPtr<FUE2DTextureAtlasAssetEditor> TextureAtlasEditorPtr = SharedThis(this);
	AtlasViewport	= SNew( SUE2DTextureAtlasEditorViewport , SharedThis(this) );
	FrameListWidget = SNew( SUE2DTextureAtlasEditorFrameList, TextureAtlasEditorPtr);

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::BuildLayout( const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost )
{
	const TSharedRef<FTabManager::FLayout> DefaultLayout = FTabManager::NewLayout("Standalone_TextureAtlasEditor_Layout_v3")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.8f)
					->SetHideTabWell(true)
					->AddTab(UE2DTextureAtlasEditorToolkitTabs::ViewportID, ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.2f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.75f)
						->SetHideTabWell(true)
						->AddTab(UE2DTextureAtlasEditorToolkitTabs::DetailsID, ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.25f)
						->AddTab(UE2DTextureAtlasEditorToolkitTabs::FrameListID, ETabState::OpenedTab)
					)
				)
			)
		);

	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(InMode, InToolkitHost, UE2DTextureAtlasEditorToolkitTabs::AppIdentifier, DefaultLayout, /*bCreateDefaultStandaloneMenu=*/ true, /*bCreateDefaultToolbar=*/ true, TextureAtlas );

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_TextureAtlasEditor", "Sprite Atlas Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();


	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(UE2DTextureAtlasEditorToolkitTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FUE2DTextureAtlasAssetEditor::SpawnTab_Viewport))
		.SetDisplayName( LOCTEXT("ViewportTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon( FAppStyle::GetAppStyleSetName() , "LevelEditor.Tabs.Viewports"));


	InTabManager->RegisterTabSpawner(UE2DTextureAtlasEditorToolkitTabs::DetailsID, FOnSpawnTab::CreateSP(this, &FUE2DTextureAtlasAssetEditor::SpawnTab_Details))
		.SetDisplayName( LOCTEXT("DetailsTab", "Details") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon( FAppStyle::GetAppStyleSetName() , "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(UE2DTextureAtlasEditorToolkitTabs::FrameListID, FOnSpawnTab::CreateSP(this, &FUE2DTextureAtlasAssetEditor::SpawnTab_FrameList))
		.SetDisplayName( LOCTEXT("TextureAtlasFrameListTabLabel", "Frame List") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon( FAppStyle::GetAppStyleSetName() , "LevelEditor.Tabs.ContentBrowser"));

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(UE2DTextureAtlasEditorToolkitTabs::ViewportID);
	InTabManager->UnregisterTabSpawner(UE2DTextureAtlasEditorToolkitTabs::DetailsID);
	InTabManager->UnregisterTabSpawner(UE2DTextureAtlasEditorToolkitTabs::FrameListID);

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FUE2DTextureAtlasAssetEditor::SpawnTab_Viewport( const FSpawnTabArgs& Args )
{
//	check( Args.GetTabId() == ViewportTabId );

	return SNew( SDockTab )
		.Label( LOCTEXT( "ViewportTitle" , "Viewport" ) )
		[
			AtlasViewport.ToSharedRef()
		];

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FUE2DTextureAtlasAssetEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
{
	TSharedPtr<SDockTab> DetailsTab = SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
		.Label(LOCTEXT("BaseDetailsTitle", "Details"))
		[
			DetailsView.ToSharedRef()
		];

	return DetailsTab.ToSharedRef();

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FUE2DTextureAtlasAssetEditor::SpawnTab_FrameList( const FSpawnTabArgs& Args )
{
	// Spawn the tab
	return SNew(SDockTab)
		.Label(LOCTEXT("TextureAtlasFrameListTab_Title", "Frame List"))
		[
			FrameListWidget.ToSharedRef()
		];

}
//-------------------------------------------------------------------------------------------


/////////////////
// Commands execution
////////////////


//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::ImportAtlas()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
	const FText Title = LOCTEXT("Import Atlas", "Import an atlas of sprite");
	const FString FileTypes = TEXT("Spine Atlas file|*.atlas");

	TArray<FString> OpenFilenames;
	if( DesktopPlatform->OpenFileDialog(
		ParentWindowWindowHandle ,
		Title.ToString() ,
		FEditorDirectories::Get().GetLastDirectory( ELastDirectory::GENERIC_IMPORT ) , // Default path.
		TEXT( "DevelopmentAssetRegistry.bin" ) ,
		FileTypes ,
		EFileDialogFlags::None ,
		OpenFilenames ) )
	{
		// Load the Atlas content
		FSpineAtlas Atlas;
		Atlas.Load( OpenFilenames[ 0 ] );

		Atlas.Apply( TextureAtlas);


	}

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DTextureAtlasAssetEditor::AddFrame()
{
	TextureAtlas->AddFrame( TEXT( "New Frame" ), 0 , 0, 0, 10, 10, false );
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE