#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class MemSimpleAccessor_2D
	{
	public:

		MemSimpleAccessor_2D()
		{
		}

		void Init(T * a_data, int a_NofSteps_X, int a_NofSteps_Y, int a_nStepSize_X, int a_nStepSize_Y)
		{
			m_data = a_data;
			
			m_NofSteps_X = a_NofSteps_X;
			m_NofSteps_Y = a_NofSteps_Y;

			m_nStepSize_X = a_nStepSize_X;
			m_nStepSize_Y = a_nStepSize_Y;
		}

		//T & operator[](int a_pos_X, int a_pos_Y)
		T & GetAt(int a_pos_X, int a_pos_Y)
		{
			Ncpp_ASSERT(a_pos_X >= 0);
			Ncpp_ASSERT(a_pos_X < m_NofSteps_X);
			
			Ncpp_ASSERT(a_pos_Y >= 0);
			Ncpp_ASSERT(a_pos_Y < m_NofSteps_Y);

			return m_data[a_pos_X * m_nStepSize_X + a_pos_Y * m_nStepSize_Y];
		}

		int GetSize_X()
		{
			return m_NofSteps_X;
		}

		int GetSize_Y()
		{
			return m_NofSteps_Y;
		}

	protected:

		T * m_data;

		int m_nStepSize_X;
		int m_nStepSize_Y;

		int m_NofSteps_X;
		int m_NofSteps_Y;
	};

}