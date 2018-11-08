#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\Size_2D.h>


namespace Ncpp
{
	class ActualIndexCalc_2D
	{
	public:

		ActualIndexCalc_2D()
		{
		}

		ActualIndexCalc_2D(const Size_2D & a_size)
		{
			InitSize(a_size);
		}

		void InitSize(const Size_2D & a_size)
		{
			InitSize(a_size.GetX(), a_size.GetY());
		}

		void InitSize(const int a_nSize_X, const int a_nSize_Y)
		{
			Ncpp_ASSERT(a_nSize_X >= 0);
			Ncpp_ASSERT(a_nSize_Y >= 0);

			m_nSize_X = a_nSize_X;
			m_nSize_Y = a_nSize_Y;
		}

		ActualIndexCalc_2D * AsIndexCalcPtr() const
		{
			return (ActualIndexCalc_2D *)this;
		}

		ActualIndexCalc_2D & AsIndexCalc() const
		{
			return *AsIndexCalcPtr();
		}

		int CalcIndex_1D(const S32Point & a_pnt) const
		{
			return CalcIndex_1D(a_pnt.GetX(), a_pnt.GetY());
		}

		int CalcIndex_1D(const int a_pos_X, const int a_pos_Y) const
		{
			Ncpp_ASSERT(a_pos_X >= 0);
			Ncpp_ASSERT(a_pos_X < m_nSize_X);

			Ncpp_ASSERT(a_pos_Y >= 0);
			Ncpp_ASSERT(a_pos_Y < m_nSize_Y);

			return a_pos_X + a_pos_Y * m_nSize_X;
		}

		int CalcX_FromIndex_1D(const int a_index_1D) const
		{
			Ncpp_ASSERT(a_index_1D < CalcSize_1D());
			return a_index_1D % m_nSize_X;
		}

		int CalcY_FromIndex_1D(const int a_index_1D) const
		{
			Ncpp_ASSERT(a_index_1D < CalcSize_1D());
			return a_index_1D / m_nSize_X;
		}

		void CalcPointFromIndex_1D(const int a_index_1D, S32Point * a_pOutPnt) const
		{
			a_pOutPnt->x = CalcX_FromIndex_1D(a_index_1D);
			a_pOutPnt->y = CalcY_FromIndex_1D(a_index_1D);
		}

		S32Point CalcPointFromIndex_1D(const int a_index_1D) const
		{
			S32Point pnt;
			CalcPointFromIndex_1D(a_index_1D, &pnt);
			return pnt;
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

		void SetSize_X(int a_nSize_X)
		{
			m_nSize_X = a_nSize_X;
		}

		void SetSize_Y(int a_nSize_Y)
		{
			m_nSize_Y = a_nSize_Y;
		}

		void CopyTo(ActualIndexCalc_2D * a_pAcc) const
		{
			a_pAcc->InitSize(m_nSize_X, m_nSize_Y);
		}

		ActualIndexCalc_2D Clone() const
		{
			ActualIndexCalc_2D acc;
			CopyTo(&acc);
			return acc;
		}

		//void AssignVirtAccessorTo(VirtArrayAccessor_2D * a_pAcc) const
		//{
		//	a_pAcc->InitSize(m_data, m_nSize_X, 1, m_nSize_Y, m_nSize_X);
		//}

		//VirtArrayAccessor_2D GenVirtAccessor() const
		//{
		//	VirtArrayAccessor_2D acc;
		//	AssignVirtAccessorTo(&acc);
		//	return acc;
		//}

	protected:

		int m_nSize_X;
		int m_nSize_Y;
	};

}