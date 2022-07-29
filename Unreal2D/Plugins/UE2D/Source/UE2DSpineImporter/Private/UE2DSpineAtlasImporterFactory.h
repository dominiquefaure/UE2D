// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UE2DSpineAtlasImporterFactory.generated.h"

UCLASS()
class UUE2EDSpineAtlasImporterFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

	// UFactory interface
	virtual FText GetToolTip() const override;
	virtual bool FactoryCanImport( const FString& Filename ) override;
	virtual UObject* FactoryCreateFile( UClass* InClass , UObject* InParent , FName InName , EObjectFlags Flags , const FString& Filename , const TCHAR* Parms , FFeedbackContext* Warn , bool& bOutOperationCanceled ) override;
	// End of UFactory interface

/*
protected:
	TSharedPtr<FJsonObject> ParseJSON( const FString& FileContents , const FString& NameForErrors , bool bSilent = false );

	static UObject* CreateNewAsset( UClass* AssetClass , const FString& TargetPath , const FString& DesiredName , EObjectFlags Flags );
	static UObject* ImportAsset( const FString& SourceFilename , const FString& TargetSubPath );
*/	static UTexture2D* ImportTexture( const FString& SourceFilename , const FString& TargetSubPath );

};
