#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{

	template<class T>
	class PtrIterator2 //: public Ncpp::Object
	{
	public:
		PtrIterator2()
		{

		}

		void Init(T * a_bgn, T * a_end, int a_nStepSize)
		{
			Ncpp_ASSERT(0 == ((a_end - a_bgn) % a_nStepSize));
			Ncpp_ASSERT(((a_end - a_bgn) / a_nStepSize) >= 0);

			m_bgn = a_bgn;
			m_end = a_end;
			m_nStepSize = a_nStepSize;
		}

		bool HasValidPos() const
		{
			//return m_bgn != m_end;
			return m_bgn != (m_end + m_nStepSize);
		}

		void MoveBgn()
		{
			Ncpp_ASSERT(HasValidPos());
			m_bgn += m_nStepSize;
		}

		void MoveEnd()
		{
			Ncpp_ASSERT(HasValidPos());
			m_end -= m_nStepSize;
		}

		T * GetBgn() const
		{
			return m_bgn;
		}

		T * GetEnd() const
		{
			return m_end;
		}

	protected:

		T * m_bgn;
		T * m_end;
		int m_nStepSize;
	};

}