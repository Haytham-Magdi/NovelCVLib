#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\Debug.h>
//#include <NovelCVLib\Ncpp\Common\indexcalc.h>




namespace Ncpp
{
	template< class T = float >
	class AvgFinder : FRM_Object(AvgFinder)
	{
	public :

		AvgFinder( )
		{
			Reset();
		}

		void AddValue( T a_val )
		{
			m_sum += a_val;
			m_nCnt++;
		}

		T FindAvg()
		{
			return m_sum / m_nCnt;
		}


		void Reset()
		{
			m_sum = 0;
			m_nCnt = 0;
		}


	protected:

		T m_sum;
		int m_nCnt;
	};

}