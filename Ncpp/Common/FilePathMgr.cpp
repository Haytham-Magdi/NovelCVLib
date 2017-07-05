#pragma once

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include <Novel-Lib\Ncpp\Common\FilePathMgr.h>


using namespace Ncpp;
//using namespace Ncpp::;



FilePathMgr::FilePathMgr( char * a_filePath )
{
	m_pathPart_Arr.SetCapacity( 500 );

	m_filePath_Arr.SetSize( strlen( a_filePath ) + 1 );

	//char buff[1000];
	char * buff = & m_filePath_Arr[ 0 ];

	strcpy( buff, a_filePath );

	m_nOrgPathLen = strlen( buff );
	//int nLen = strlen( buff );

	//int nSpn = strcspn( buff, "\\" );

	//int nBgn = nSpn + 1;


	//while( 0 != nSpn )
	//{
	//	nSpn = strcspn( & buff[ nBgn ], "\\" );
	//	nBgn += nSpn + 1;
	//}

	//nSpn = strcspn( & buff[ nLen ], "\\" );

	char * pch;
	//printf ("Splitting string \"%s\" into tokens:\n",str);

	pch = strtok ( buff, "\\" );

	while (pch != NULL)
	{
		m_pathPart_Arr.PushBack( pch );
		//printf ("%s\n",pch);
		pch = strtok (NULL, "\\");
	}

	//for( int i=0; i < m_pathPart_Arr.GetSize(); i++ )
	//{
	//	pch = m_pathPart_Arr[ i ];
	//}


}




void FilePathMgr::GetFilePath_To_Level( FixedVector< char > & a_rOut_Arr, 
	int a_nLevel )
{
	//Ncpp_ASSERT( a_rOut_Arr.GetCapacity() > m_nOrgPathLen );
	a_rOut_Arr.SetSize( m_nOrgPathLen + 1 );
	a_rOut_Arr.ResetSize();

	int nLevel = a_nLevel;

	if( -1 == nLevel )
		nLevel = m_pathPart_Arr.GetSize() - 1;

	Ncpp_ASSERT( nLevel >= 0 );
	Ncpp_ASSERT( nLevel < m_pathPart_Arr.GetSize() );



	int nOutCnt = 0;
	for( int i=0; i <= nLevel; i++ )
	{
		nOutCnt += sprintf( & a_rOut_Arr[ nOutCnt ],
			"%s", m_pathPart_Arr[ i ] );

		if( i < nLevel )
		{
			nOutCnt += sprintf( & a_rOut_Arr[ nOutCnt ], "\\" );
		}



		//char * out_Buf = & a_rOut_Arr.GetBack() + 1;

		//strcpy( out_Buf, m_pathPart_Arr[ i ] );

		//a_rOut_Arr.IncSize( strlen( m_pathPart_Arr[ i ] ) );
	}

	a_rOut_Arr.SetSize( nOutCnt + 1 );

}


char * FilePathMgr::GetFileName_At( int a_nLevel )
{
	int nLevel = a_nLevel;

	if( -1 == nLevel )
		nLevel = m_pathPart_Arr.GetSize() - 1;

	Ncpp_ASSERT( nLevel >= 0 );
	Ncpp_ASSERT( nLevel < m_pathPart_Arr.GetSize() );

	return m_pathPart_Arr[ nLevel ];
}


void FilePathMgr::GetFileTitle( FixedVector< char > & a_rOut_Arr )
{
	int nFileNm_Len = strlen( GetFileName_At() );

	a_rOut_Arr.SetSize( nFileNm_Len + 1 );
	//a_rOut_Arr.ResetSize();


	strcpy( a_rOut_Arr.GetHeadPtr(), 
		GetFileName_At() );


	char * pDot;

	pDot = strrchr( a_rOut_Arr.GetHeadPtr(), '.' );

	if( NULL != pDot )
		*pDot = 0;


}




