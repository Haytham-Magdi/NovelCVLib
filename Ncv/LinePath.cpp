#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
#include <vector>
#include <NovelCVLib\OpenCV\Channel.h>
#include <NovelCVLib\OpenCV\Image.h>
#include <NovelCVLib\OpenCV\funcs1.h>

#include <NovelCVLib\Ncv\LinePath.h>

namespace Ncv
{
	using namespace Ncpp;
	//using namespace Ncpp::Math;

	LinePath::LinePath( int a_x1, int a_y1, int a_x2, int a_y2 ) :
//		m_x1(a_x1), m_y1(a_y1), m_x2(a_x2), m_y2(a_y2)
		m_bgnPnt(a_x1, a_y1), m_endPnt(a_x2, a_y2), m_nDoneSteps(0)
	{

		m_curPnt = m_bgnPnt;

		//m_nReqSteps = abs( (int) ( m_endPnt.x - m_bgnPnt.x ) );

		//const F32Point deltaPnt = F32Point::Sub( (F32Point)m_endPnt, (F32Point)m_bgnPnt );
		F32Point deltaPnt = F32Point::Sub( (F32Point)m_endPnt, (F32Point)m_bgnPnt );

		m_nReqSteps = (int) ( deltaPnt.CalcMag() + 0.55555555555 );

		m_stepPnt = deltaPnt.DividBy( m_nReqSteps );

		m_stepPnt.x = (int)( m_stepPnt.x * 1000 ) / (float) 1000;
		m_stepPnt.y = (int)( m_stepPnt.y * 1000 ) / (float) 1000;

		 

		//m_stepPnt = { 1, 0 };		
	}


	bool LinePath::MoveNext()
	{
		F32Point lastRoundPnt;

		do
		{
			if( m_nDoneSteps >= m_nReqSteps )
				return false;

			lastRoundPnt = m_curPnt.Round();
			m_curPnt.IncBy( m_stepPnt );
			
			m_nDoneSteps++;

		//}while( true == F32Point::Compare( m_curPnt.Round(), lastRoundPnt ) );
		}while( false );

		return true;
	}







}