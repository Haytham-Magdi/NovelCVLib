#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Math\mathLib.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>

namespace Ncv
{
	//using namespace Ncpp::Math;


	class IOMgr
	{
	public:

		class IIOMgrCore
		{
		public:

			virtual void ReadString( char * a_sKey, char * a_buff ) = 0;
			virtual bool ValueExists( char * a_sKey ) = 0;
		};


		static IIOMgrCore * GetCore()
		{
			//return nullptr;
			return m_pCore;
			
		}

		static void SetCore(IIOMgrCore * a_pCore)
		{			
			m_pCore = a_pCore;			
		}

		static void ReadString( char * a_sKey, char * a_buff )
		{
			GetCore()->ReadString( a_sKey, a_buff );
		}

		static bool ValueExists( char * a_sKey )
		{
			return GetCore()->ValueExists( a_sKey );
		}

					


		static float ReadFloat( char * a_sKey )
		{
			m_tmpBuff[0] = 0;
			IOMgr::ReadString(a_sKey, m_tmpBuff);
			
			return atof(m_tmpBuff);
		}

		static int ReadInt( char * a_sKey )
		{
			m_tmpBuff[0] = 0;
			IOMgr::ReadString(a_sKey, m_tmpBuff);
			
			return atoi(m_tmpBuff);
		}


	protected:

		static IIOMgrCore * m_pCore;

		static char m_tmpBuff[100];

	};


}