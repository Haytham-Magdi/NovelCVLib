#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class MemSimpleAccessor_2D
	{
	public:

		MemSimpleAccessor_2D()
		{
		}

		void Init(T * a_data, int a_nIndexSize_X, int a_nIndexSize_Y, int a_nStepSize_X, int a_nStepSize_Y)
		{
			m_data = a_data;
			
			m_nIndexSize_X = a_nIndexSize_X;
			m_nIndexSize_Y = a_nIndexSize_Y;

			m_nStepSize_X = a_nStepSize_X;
			m_nStepSize_Y = a_nStepSize_Y;
		}

		//T & operator[](int a_pos_X, int a_pos_Y)
		T & GetAt(int a_pos_X, int a_pos_Y)
		{
			Ncpp_ASSERT(a_pos_X >= 0);
			Ncpp_ASSERT(a_pos_X < m_nIndexSize_X);
			
			Ncpp_ASSERT(a_pos_Y >= 0);
			Ncpp_ASSERT(a_pos_Y < m_nIndexSize_Y);

			return m_data[a_pos_X * m_nStepSize_X + a_pos_Y * m_nStepSize_Y];
		}

		int GetSize_X()
		{
			return m_nIndexSize_X;
		}

		int GetSize_Y()
		{
			return m_nIndexSize_Y;
		}

	protected:

		T * m_data;

		int m_nStepSize_X;
		int m_nStepSize_Y;

		int m_nIndexSize_X;
		int m_nIndexSize_Y;
	};

}