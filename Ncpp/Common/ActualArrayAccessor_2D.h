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

		void Init(T * a_data, const Size_2D & a_size)
		{
			Init(a_data, a_size.GetX(), a_size.GetY());
		}

		void Init(T * a_data, const int a_nSize_X, const int a_nSize_Y)
		{
			Ncpp_ASSERT(a_nSize_X >= 0);
			Ncpp_ASSERT(a_nSize_Y >= 0);

			m_data = a_data;

			m_nSize_X = a_nSize_X;
			m_nSize_Y = a_nSize_Y;
		}

		const T & GetAt(const int a_pos_X, const int a_pos_Y) const
		{
			Ncpp_ASSERT(a_pos_X >= 0);
			Ncpp_ASSERT(a_pos_X < m_nSize_X);

			Ncpp_ASSERT(a_pos_Y >= 0);
			Ncpp_ASSERT(a_pos_Y < m_nSize_Y);

			//return m_data[a_pos_X * m_nStepSize_X + a_pos_Y * m_nStepSize_Y];
			return m_data[a_pos_X + a_pos_Y * m_nSize_X];
		}

		T * GetData() const
		{
			return m_data;
		}

		int GetSize_X() const
		{
			return m_nSize_X;
		}

		int GetSize_Y() const
		{
			return m_nSize_Y;
		}

		int CalcSize_1D() const
		{
			return m_nSize_X * m_nSize_Y;
		}

		Size_2D GetSize() const
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

		void CopyTo(ActualArrayAccessor_2D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nSize_X, m_nSize_Y);
		}

		ActualArrayAccessor_2D<T> Clone() const
		{
			ActualArrayAccessor_2D<T> arr;
			CopyTo(&arr);
			return arr;
		}

		void AssignVirtAccessorTo(VirtArrayAccessor_2D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nSize_X, 1, m_nSize_Y, m_nSize_X);
		}

		VirtArrayAccessor_2D<T> GenVirtAccessor() const
		{
			VirtArrayAccessor_2D<T> arr;
			AssignVirtAccessorTo(&arr);
			return arr;
		}

	protected:

		T * m_data;

		int m_nSize_X;
		int m_nSize_Y;
	};

}