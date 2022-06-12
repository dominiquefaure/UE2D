// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteAtlasAssetEditor.h"

#include "DesktopPlatformModule.h"
#include "EditorDirectories.h"

#include "UE2DSpriteAtlasEditorCommands.h"
#include "UE2DSpriteAtlasEditorViewport.h"
#include "UE2DSpriteAtlasEditorFrameList.h"
#include <importers/SpineImporters/SpineAtlas.h>


#define LOCTEXT_NAMESPACE "SpriteAtlasEditor"

namespace UE2DSpriteAtlasEditorToolkitTabs
{
	static const FName AppIdentifier("SpriteAtlasEditorApp");
	static const FName ViewportID("Viewport");
	static const FName DetailsID("Details");
	static const FName FrameListID("FrameList");
}



//-------------------------------------------------------------------------------------------
FUE2DSpriteAtlasAssetEditor::FUE2DSpriteAtlasAssetEditor()
{

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
FText FUE2DSpriteAtlasAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "SpriteAtlas Editor");
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FName FUE2DSpriteAtlasAssetEditor::GetToolkitFName() const
{
	return FName("SpriteAtlasEditor");
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FLinearColor FUE2DSpriteAtlasAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FString FUE2DSpriteAtlasAssetEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("SpriteAtlasEditor");
}
//-------------------------------------------------------------------------------------------



///////////////////////////////
// Editor Initialization

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::Initialize( UUE2DSpriteAtlas* Atlas, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost )
{
	if( Atlas == nullptr)
	{
		return;
	}

	SpriteAtlas	=	Atlas;


	// Register the Commands before linking it in any of the widgets / menu
	FUE2DSpriteAtlasEditorCommands::Register();
	BindCommands();
	CreateWidgets();

	BuildLayout( InMode , InToolkitHost );

	ExtendToolbar();
	RegenerateMenusAndToolbars();

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::ExtendToolbar()
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
					ToolbarBuilder.AddToolBarButton(FUE2DSpriteAtlasEditorCommands::Get().ImportAtlas);
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
					ToolbarBuilder.AddToolBarButton(FUE2DSpriteAtlasEditorCommands::Get().AddFrame);
				}
				ToolbarBuilder.EndSection();
			})
	);

	AddToolbarExtender(ToolbarExtender);


}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::BindCommands()
{
	FUE2DSpriteAtlasEditorCommands::Register();
	const FUE2DSpriteAtlasEditorCommands& Commands = FUE2DSpriteAtlasEditorCommands::Get();

	const TSharedRef<FUICommandList>& CommandList = GetToolkitCommands();

	CommandList->MapAction(
		Commands.ImportAtlas,
		FExecuteAction::CreateSP(this, &FUE2DSpriteAtlasAssetEditor::ImportAtlas));

	CommandList->MapAction(
		Commands.AddFrame,
		FExecuteAction::CreateSP(this, &FUE2DSpriteAtlasAssetEditor::AddFrame));

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::CreateWidgets()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyModule.CreateDetailView(Args);

	DetailsView->SetObject(SpriteAtlas);


	TSharedPtr<FUE2DSpriteAtlasAssetEditor> SpriteAtlasEditorPtr = SharedThis(this);
	AtlasViewport	= SNew( SUE2DSpriteAtlasEditorViewport , SharedThis(this) );
	FrameListWidget = SNew( SUE2DSpriteAtlasEditorFrameList, SpriteAtlasEditorPtr);

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::BuildLayout( const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost )
{
	const TSharedRef<FTabManager::FLayout> DefaultLayout = FTabManager::NewLayout("Standalone_SpriteAtlasEditor_Layout_v3")
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
					->AddTab(UE2DSpriteAtlasEditorToolkitTabs::ViewportID, ETabState::OpenedTab)
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
						->AddTab(UE2DSpriteAtlasEditorToolkitTabs::DetailsID, ETabState::OpenedTab)
					)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.25f)
						->AddTab(UE2DSpriteAtlasEditorToolkitTabs::FrameListID, ETabState::OpenedTab)
					)
				)
			)
		);

	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(InMode, InToolkitHost, UE2DSpriteAtlasEditorToolkitTabs::AppIdentifier, DefaultLayout, /*bCreateDefaultStandaloneMenu=*/ true, /*bCreateDefaultToolbar=*/ true, SpriteAtlas );

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_SpriteAtlasEditor", "Sprite Atlas Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();


	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(UE2DSpriteAtlasEditorToolkitTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FUE2DSpriteAtlasAssetEditor::SpawnTab_Viewport))
		.SetDisplayName( LOCTEXT("ViewportTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));


	InTabManager->RegisterTabSpawner(UE2DSpriteAtlasEditorToolkitTabs::DetailsID, FOnSpawnTab::CreateSP(this, &FUE2DSpriteAtlasAssetEditor::SpawnTab_Details))
		.SetDisplayName( LOCTEXT("DetailsTab", "Details") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(UE2DSpriteAtlasEditorToolkitTabs::FrameListID, FOnSpawnTab::CreateSP(this, &FUE2DSpriteAtlasAssetEditor::SpawnTab_FrameList))
		.SetDisplayName( LOCTEXT("SpriteAtlasFrameListTabLabel", "Frame List") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.ContentBrowser"));

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(UE2DSpriteAtlasEditorToolkitTabs::ViewportID);
	InTabManager->UnregisterTabSpawner(UE2DSpriteAtlasEditorToolkitTabs::DetailsID);
	InTabManager->UnregisterTabSpawner(UE2DSpriteAtlasEditorToolkitTabs::FrameListID);

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FUE2DSpriteAtlasAssetEditor::SpawnTab_Viewport( const FSpawnTabArgs& Args )
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
TSharedRef<SDockTab> FUE2DSpriteAtlasAssetEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
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
TSharedRef<SDockTab> FUE2DSpriteAtlasAssetEditor::SpawnTab_FrameList( const FSpawnTabArgs& Args )
{
	// Spawn the tab
	return SNew(SDockTab)
		.Label(LOCTEXT("SpriteAtlasFrameListTab_Title", "Frame List"))
		[
			FrameListWidget.ToSharedRef()
		];

}
//-------------------------------------------------------------------------------------------


/////////////////
// Commands execution
////////////////


//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::ImportAtlas()
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

		Atlas.Apply( SpriteAtlas);


	}

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteAtlasAssetEditor::AddFrame()
{
	SpriteAtlas->AddFrame( TEXT( "New Frame" ), 0, 0, 10, 10, false );
}
//-------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE