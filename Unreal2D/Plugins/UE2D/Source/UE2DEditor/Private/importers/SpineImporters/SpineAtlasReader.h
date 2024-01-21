// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "SpineAtlasPage.h"
#include "SpineAtlasRegion.h"


class FSpineAtlasReader
{

public:

	void Load( const FString& InFilepath );

	// did we have already parsed all the lines
	int RemainingLines();
	bool IsFinished();

	bool IsEmptyLine();
	bool IsValuesLine();

	FString GetString( bool advance );
	void GetValues( FString* OutString , TArray<int>* OutInt ,bool advance );

	bool AdvanceLine();



private:

	TArray<FString>Lines;

	// index of the Current Line
	int Index;
};

