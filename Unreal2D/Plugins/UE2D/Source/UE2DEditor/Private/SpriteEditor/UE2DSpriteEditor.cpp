// Fill out your copyright notice in the Description page of Project Settings.


#include "UE2DSpriteEditor.h"

#include "DesktopPlatformModule.h"
#include "EditorDirectories.h"

#include "UE2DSpriteEditorViewport.h"
#include <importers/SpineImporters/SpineAtlas.h>


#define LOCTEXT_NAMESPACE "SpriteEditor"

namespace UE2DSpriteEditorToolkitTabs
{
	static const FName AppIdentifier("SpriteEditorApp");
	static const FName ViewportID("Viewport");
	static const FName DetailsID("Details");
}



//-------------------------------------------------------------------------------------------
FUE2DSpriteEditor::FUE2DSpriteEditor()
{

}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
FText FUE2DSpriteEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Sprite Editor");
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FName FUE2DSpriteEditor::GetToolkitFName() const
{
	return FName("SpriteEditor");
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FLinearColor FUE2DSpriteEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
FString FUE2DSpriteEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("SpriteEditor");
}
//-------------------------------------------------------------------------------------------



///////////////////////////////
// Editor Initialization

//-------------------------------------------------------------------------------------------
void FUE2DSpriteEditor::Initialize( UUE2DSpriteArmature* Armature, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost )
{
	if( Armature == nullptr)
	{
		return;
	}

	SpriteArmature	=	Armature;


	CreateWidgets();

	BuildLayout( InMode , InToolkitHost );

	RegenerateMenusAndToolbars();

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteEditor::CreateWidgets()
{
	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyModule.CreateDetailView(Args);

	DetailsView->SetObject(SpriteArmature);


	TSharedPtr<FUE2DSpriteEditor> TextureAtlasEditorPtr = SharedThis(this);
	SpriteViewport	= SNew( SUE2DSpriteEditorViewport , SharedThis(this) );
}
//-------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------
void FUE2DSpriteEditor::BuildLayout( const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost )
{
	const TSharedRef<FTabManager::FLayout> DefaultLayout = FTabManager::NewLayout("Standalone_SpriteEditor_Layout")
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
					->AddTab(UE2DSpriteEditorToolkitTabs::ViewportID, ETabState::OpenedTab)
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
						->AddTab( UE2DSpriteEditorToolkitTabs::DetailsID, ETabState::OpenedTab)
					)
				)
			)
		);

	// Initialize the asset editor and spawn nothing (dummy layout)
	InitAssetEditor(InMode, InToolkitHost, UE2DSpriteEditorToolkitTabs::AppIdentifier, DefaultLayout, /*bCreateDefaultStandaloneMenu=*/ true, /*bCreateDefaultToolbar=*/ true, SpriteArmature );

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteEditor::RegisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_TextureEditor", "Texture Atlas Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();


	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner( UE2DSpriteEditorToolkitTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FUE2DSpriteEditor::SpawnTab_Viewport))
		.SetDisplayName( LOCTEXT("ViewportTab", "Viewport") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports"));


	InTabManager->RegisterTabSpawner( UE2DSpriteEditorToolkitTabs::DetailsID, FOnSpawnTab::CreateSP(this, &FUE2DSpriteEditor::SpawnTab_Details))
		.SetDisplayName( LOCTEXT("DetailsTab", "Details") )
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon( FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Details"));

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void FUE2DSpriteEditor::UnregisterTabSpawners( const TSharedRef<FTabManager>& InTabManager )
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner( UE2DSpriteEditorToolkitTabs::ViewportID);
	InTabManager->UnregisterTabSpawner( UE2DSpriteEditorToolkitTabs::DetailsID);

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FUE2DSpriteEditor::SpawnTab_Viewport( const FSpawnTabArgs& Args )
{
//	check( Args.GetTabId() == ViewportTabId );

	return SNew( SDockTab )
		.Label( LOCTEXT( "ViewportTitle" , "Viewport" ) )
		[
			SpriteViewport.ToSharedRef()
		];

}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
TSharedRef<SDockTab> FUE2DSpriteEditor::SpawnTab_Details( const FSpawnTabArgs& Args )
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


#undef LOCTEXT_NAMESPACE