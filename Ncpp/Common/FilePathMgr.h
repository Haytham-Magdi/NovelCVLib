#pragma once

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include <NovelCVLib\Ncpp\Common\commonLib.h>


namespace Ncpp
{
	class FilePathMgr
	{
	public:
		FilePathMgr( char * a_filePath );

		void GetFilePath_To_Level( FixedVector< char > & a_rOut_Arr, 
			int a_nLevel = -1 );

		char * GetFileName_At( int a_nLevel = -1 );

		void GetFileTitle( FixedVector< char > & a_rOut_Arr );



	protected:
		FixedVector< char > m_filePath_Arr;
		FixedVector< char * > m_pathPart_Arr;

		int m_nOrgPathLen;

	};
}

