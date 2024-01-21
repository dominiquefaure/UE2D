// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "UE2DSpineAtlasImporterFactory.h"
#include "TextureAtlas/UE2DTextureAtlas.h"

#include "AssetToolsModule.h"
#include "Misc/FileHelper.h"

#include "UE2DSpineDataModel.h"


#define LOCTEXT_NAMESPACE "UE2DSpineImporter"

//---------------------------------------------------------------------------------------------
UUE2EDSpineAtlasImporterFactory::UUE2EDSpineAtlasImporterFactory( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	bCreateNew		=	false;
	bEditorImport	=	true;

	SupportedClass	=	UUE2DTextureAtlas::StaticClass();

	Formats.Add( TEXT( "atlas;Spine Atlas file" ) );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
FText UUE2EDSpineAtlasImporterFactory::GetToolTip() const
{
	return LOCTEXT( "UUE2DSpineAtlasImporterFactory" , "Atlas exported from Spine" );
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
bool UUE2EDSpineAtlasImporterFactory::FactoryCanImport( const FString& Filename )
{
	return true;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UObject* UUE2EDSpineAtlasImporterFactory::FactoryCreateFile( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , const FString& Filename , const TCHAR* Parms , FFeedbackContext* Warn , bool& bOutOperationCanceled )
{
	FString rawString;
	if( !FFileHelper::LoadFileToString( rawString , *Filename ) )
	{
		return nullptr;
	}

	FString CurrentSourcePath , FilenameNoExtension , UnusedExtension;
	const FString LongPackagePath			=	 FPackageName::GetLongPackagePath( InParent->GetOutermost()->GetPathName() );
	FPaths::Split( UFactory::GetCurrentFilename() , CurrentSourcePath , FilenameNoExtension , UnusedExtension );


	// Load the Atlas content
	FUE2DSpineAtlas SpineAtlas;
	SpineAtlas.Load( Filename );

	UUE2DTextureAtlas* TextureAtlas			=	NewObject<UUE2DTextureAtlas>( InParent , InName , Flags );

	const FString TargetTexturePath			=	LongPackagePath / TEXT( "Textures" );

	int32 PageCount							=	SpineAtlas.Pages.Num();
	FUE2DSpineAtlasPage* CurrentPage;
	FUE2DSpineAtlasRegion* CurrentRegion;
	int32 RegionCount;

	for( int i = 0 ; i < PageCount ; i ++ )
	{
		CurrentPage							=	&( SpineAtlas.Pages[ i ] );

		// Import the Texture
		const FString SourceTextureFilename = FPaths::Combine( *CurrentSourcePath , CurrentPage->TextureName );
		UTexture2D* Texture					=	ImportTexture( SourceTextureFilename , TargetTexturePath );

		RegionCount							=	CurrentPage->Regions.Num();

		for( int32 j = 0 ; j < RegionCount ; j ++ )
		{
			CurrentRegion					=	&(CurrentPage->Regions[ j ]);

			TextureAtlas->AddFrame( Texture ,
				CurrentRegion->Name ,
				CurrentRegion->BoundX ,
				CurrentRegion->BoundY ,
				CurrentRegion->BoundWidth ,
				CurrentRegion->BoundHeight ,
				CurrentRegion->rotated );
		}
	}

	return TextureAtlas;
}
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
UTexture2D* UUE2EDSpineAtlasImporterFactory::ImportTexture( const FString& SourceFilename , const FString& TargetSubPath )
{
	FAssetToolsModule& AssetToolsModule = FModuleManager::GetModuleChecked<FAssetToolsModule>( "AssetTools" );

	TArray<FString> FileNames;
	FileNames.Add( SourceFilename );

	TArray<UObject*> ImportedAssets = AssetToolsModule.Get().ImportAssets( FileNames , TargetSubPath );
	return ( ImportedAssets.Num() > 0 ) ? Cast< UTexture2D>(ImportedAssets[ 0 ] ) : nullptr;

}
//---------------------------------------------------------------------------------------------

#undef LOCTEXT_NAMESPACE