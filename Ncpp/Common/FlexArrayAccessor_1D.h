#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class FlexArrayAccessor_1D
	{
	public:

		FlexArrayAccessor_1D()
		{
		}

		void Init(T * a_data, int a_nofSteps, int a_nStepSize)
		{
			m_data = a_data;
			m_nofSteps = a_nofSteps;
			m_nStepSize = a_nStepSize;
		}

		const T & operator[](int a_pos)
		{
			Ncpp_ASSERT(a_pos >= 0);
			Ncpp_ASSERT(a_pos < m_nofSteps);

			return m_data[a_pos * m_nStepSize];
		}

		const int GetSize()
		{
			return m_nofSteps;
		}

		const T * GetData()
		{
			return m_data;
		}

		const int GetStepSize()
		{
			return m_nStepSize;
		}

		void SetSize(int a_nofSteps)
		{
			m_nofSteps = a_nofSteps;
		}

		void SetData(T * a_data)
		{
			m_data = a_data;
		}

		void SetStepSize(int a_nStepSize)
		{
			m_nStepSize = a_nStepSize;
		}


	protected:

		T * m_data;
		int m_nStepSize;
		int m_nofSteps;
	};
	
}