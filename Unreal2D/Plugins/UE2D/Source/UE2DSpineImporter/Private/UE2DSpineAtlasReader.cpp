
#include "UE2DSpineAtlasReader.h"

#include "Misc/FileHelper.h"


//-----------------------------------------------------------------------------------------------------
void FUE2DSpineAtlasReader::Load( const FString& InFilepath )
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
int FUE2DSpineAtlasReader::RemainingLines()
{
	return Lines.Num() - Index;
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FUE2DSpineAtlasReader::IsFinished()
{
	return ( Index >= Lines.Num() );
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FUE2DSpineAtlasReader::IsEmptyLine()
{
	return (Lines[ Index ].Len() == 0 );
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
bool FUE2DSpineAtlasReader::IsValuesLine()
{
	return ( Lines[ Index ].Contains( ":" ) );
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
FString FUE2DSpineAtlasReader::GetString( bool Advance )
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
bool FUE2DSpineAtlasReader::AdvanceLine()
{
	Index ++;

	return IsFinished();
}
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
void FUE2DSpineAtlasReader::GetValues( FString* OutString , TArray<int>* OutInt , bool Advance )
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
