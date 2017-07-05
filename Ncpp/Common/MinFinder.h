#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <Novel-Lib\Ncpp\Common\Debug.h>
//#include <Novel-Lib\Ncpp\Common\indexcalc.h>




namespace Ncpp
{
	template< class T >
	class MinFinder : FRM_Object
	{
	public :

		MinFinder( T a_valOrg = 10000000 )
		{
			m_valOrg = a_valOrg;
			m_valCur = a_valOrg;
		}

		void AddValue( T a_val )
		{
			if( a_val < m_valCur )
				m_valCur = a_val;
		}

		T FindMin()
		{
			return m_valCur;
		}


		void Reset()
		{
			m_valCur = m_valOrg;
		}


	protected:

		T m_valOrg;
		T m_valCur;
	};

}
