#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\OffsetCalc_1D.h>


namespace Ncpp
{

	template<class T>
	class PtrIterator2 //: public Ncpp::Object
	{
	public:

		PtrIterator2(T * a_bgn, T * a_end, int a_nStepSize)
		{
			Ncpp_ASSERT(0 == ((a_end - a_bgn) % a_nStepSize));
			Ncpp_ASSERT(((a_end - a_bgn) / a_nStepSize) >= 0);

			m_bgn = a_bgn;
			m_end = a_end;
			m_nStepSize = a_nStepSize;
		}

		bool CanMove()
		{
			return m_bgn != m_end;
		}

		void MoveBgn()
		{
			Ncpp_ASSERT(!CanMove());
			m_bgn += m_nStepSize;
		}

		void MoveEnd()
		{
			Ncpp_ASSERT(!CanMove());
			m_end -= m_nStepSize;
		}

		T * GetBgn()
		{
			return m_bgn;
		}

		T * GetEnd()
		{
			return m_end;
		}

	protected:

		T * m_bgn;
		T * m_end;
		int m_nStepSize;
	};

}