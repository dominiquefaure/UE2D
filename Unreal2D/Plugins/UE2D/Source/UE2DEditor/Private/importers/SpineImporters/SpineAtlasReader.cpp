// Copyright 2022-2024 Dominique Faure. All Rights Reserved.

#include "SpineAtlasReader.h"

#include "Misc/FileHelper.h"

#include "SpineAtlasPage.h"

//-----------------------------------------------------------------------------------------------------
void FSpineAtlasReader::Load( const FString& InFilepath )
{
	FString FileContent;
	if( FFileHelper::LoadFileToString(/*out*/ FileContent , *InFilepath ) )
	{
		int Count	=	FileContent.ParseIntoArrayLines( Lines , false );

		for( int i = 0; i < Count; i++ )
		{
			FString CurrentLine	=	Lines[ i ];
			UE_LOG( LogTemp , Warning , TEXT("%s") , *CurrentLine );

		}
	}

	Index	=	0;
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
int FSpineAtlasReader::RemainingLines()
{
	return Lines.Num() - Index;
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FSpineAtlasReader::IsFinished()
{
	return ( Index >= Lines.Num() );
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FSpineAtlasReader::IsEmptyLine()
{
	return (Lines[ Index ].Len() == 0 );
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FSpineAtlasReader::IsValuesLine()
{
	return ( Lines[ Index ].Contains( ":" ) );
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
FString FSpineAtlasReader::GetString( bool Advance )
{
	FString Text	=	Lines[ Index ];

	if( Advance )
	{
		Index++;
	}
	return Text;
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FSpineAtlasReader::AdvanceLine()
{
	Index ++;

	return IsFinished();
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
void FSpineAtlasReader::GetValues( FString* OutString , TArray<int>* OutInt , bool Advance )
{
	if( !IsValuesLine() )
	{
		return;
	}

	FString Values;
	FString LeftValue;

	Lines[ Index ].Split( FString( ":" ) , OutString , &Values );

	while( Values.Contains( "," ) )
	{
		Values.Split( FString( "," ) , &LeftValue , &Values );
		OutInt->Add( FCString::Atoi( *LeftValue ) );
	}

	OutInt->Add( FCString::Atoi( *Values ) );

	if( Advance )
	{
		Index++;
	}
}
//-----------------------------------------------------------------------------------------------------
