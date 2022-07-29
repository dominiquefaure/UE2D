// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Internationalization/Internationalization.h"


//DEFINE_LOG_CATEGORY( LogUE2DSpineImporter );

#define LOCTEXT_NAMESPACE "UE2DSpineImporter"


//////////////////////////////////////////////////////////////////////////
// FSpriterImporterModule

class FUE2DSprineImporterModule : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override
	{
	}

	virtual void ShutdownModule() override
	{
	}
};

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_MODULE( FUE2DSprineImporterModule , UE2DSprineImporter );

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
