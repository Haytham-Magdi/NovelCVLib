#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class MemSimpleAccessor_1D
	{
	public:

		MemSimpleAccessor_1D()
		{
		}

		void Init(T * a_data, int a_NofElms, int a_nStepSize)
		{
			m_data = a_data;
			m_NofElms = a_NofElms;
			m_nStepSize = a_nStepSize;
		}

		T & operator[](int a_pos)
		{
			Ncpp_ASSERT(a_pos >= 0);
			Ncpp_ASSERT(a_pos < m_NofElms);

			return m_data[a_pos * m_nStepSize];
		}

		int GetSize()
		{
			return m_NofElms;
		}

	protected:

		T * m_data;
		int m_nStepSize;
		int m_NofElms;
	};
	
}