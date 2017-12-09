#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_1D.h>
#include <NovelCVLib\Ncpp\Common\Size_2D.h>


namespace Ncpp
{
	template<class T>
	class ActualArrayAccessor_2D
	{
	public:

		ActualArrayAccessor_2D()
		{
		}

		void Init(T * a_data, int a_nSize_X, int a_nSize_Y)
		{
			m_data = a_data;

			m_nSize_X = a_nSize_X;
			m_nSize_Y = a_nSize_Y;
		}

		const T & GetAt(int a_pos_X, int a_pos_Y)
		{
			Ncpp_ASSERT(a_pos_X >= 0);
			Ncpp_ASSERT(a_pos_X < m_nSize_X);

			Ncpp_ASSERT(a_pos_Y >= 0);
			Ncpp_ASSERT(a_pos_Y < m_nSize_Y);

			return m_data[a_pos_X * m_nStepSize_X + a_pos_Y * m_nStepSize_Y];
		}

		const T * GetData()
		{
			return m_data;
		}

		const int GetSize_X()
		{
			return m_nSize_X;
		}

		const int GetSize_Y()
		{
			return m_nSize_Y;
		}

		const int CalcSize_1D()
		{
			return m_nSize_X * m_nSize_Y;
		}

		const Size_2D GetSize()
		{
			return Size_2D(m_nSize_X, m_nSize_Y);
		}

		void SetData(T * a_data)
		{
			m_data = a_data;
		}

		void SetSize_X(int a_nSize_X)
		{
			m_nSize_X = a_nSize_X;
		}

		void SetSize_Y(int a_nSize_Y)
		{
			m_nSize_Y = a_nSize_Y;
		}

		void CopyTo(ActualArrayAccessor_2D<T> * a_pAcc)
		{
			a_pAcc->Init(m_data, m_nSize_X, m_nStepSize_X, m_nSize_Y, m_nStepSize_Y);
		}

		ActualArrayAccessor_2D<T> Clone()
		{
			ActualArrayAccessor_2D<T> arr;
			CopyTo(&arr);
			return arr;
		}

	protected:

		T * m_data;

		int m_nSize_X;
		int m_nSize_Y;
	};

}