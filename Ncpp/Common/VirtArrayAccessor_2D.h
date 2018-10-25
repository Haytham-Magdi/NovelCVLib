#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_1D.h>
#include <NovelCVLib\Ncpp\Common\Size_2D.h>


namespace Ncpp
{
	template<class T>
	class VirtArrayAccessor_2D
	{
	public:

		VirtArrayAccessor_2D()
		{
		}

		void Init(const T * a_data, const int a_nofSteps_X, const int a_nStepSize_X, const int a_nofSteps_Y, const int a_nStepSize_Y)
		{
			m_data = (T *)a_data;

			m_nofSteps_X = a_nofSteps_X;
			m_nStepSize_X = a_nStepSize_X;

			m_nofSteps_Y = a_nofSteps_Y;
			m_nStepSize_Y = a_nStepSize_Y;
		}

		T & GetAt(const int a_pos_X, const int a_pos_Y) const
		{
			Ncpp_ASSERT(a_pos_X >= 0);
			Ncpp_ASSERT(a_pos_X < m_nofSteps_X);

			Ncpp_ASSERT(a_pos_Y >= 0);
			Ncpp_ASSERT(a_pos_Y < m_nofSteps_Y);

			return m_data[a_pos_X * m_nStepSize_X + a_pos_Y * m_nStepSize_Y];
		}

		T * GetData() const
		{
			return m_data;
		}

		int GetSize_X() const
		{
			return m_nofSteps_X;
		}

		int GetStepSize_X() const
		{
			return m_nStepSize_X;
		}

		int GetSize_Y() const
		{
			return m_nofSteps_Y;
		}

		int GetStepSize_Y() const
		{
			return m_nStepSize_Y;
		}

		int CalcSize_1D() const
		{
			return m_nofSteps_X * m_nofSteps_Y;
		}

		Size_2D GetSize() const
		{
			return Size_2D(m_nofSteps_X, m_nofSteps_Y);
		}

		void SetData(T * a_data)
		{
			m_data = a_data;
		}

		void SetSize_X(const int a_nofSteps_X)
		{
			m_nofSteps_X = a_nofSteps_X;
		}

		void SetStepSize_X(const int a_nStepSize_X)
		{
			m_nStepSize_X = a_nStepSize_X;
		}

		void SetSize_Y(const int a_nofSteps_Y)
		{
			m_nofSteps_Y = a_nofSteps_Y;
		}

		void SetStepSize_Y(const int a_nStepSize_Y)
		{
			m_nStepSize_Y = a_nStepSize_Y;
		}

		void AssignAccessor_X_To(VirtArrayAccessor_1D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nofSteps_X, m_nStepSize_X);
		}

		VirtArrayAccessor_1D<T> GenAccessor_X() const
		{
			VirtArrayAccessor_1D<T> acc;
			AssignAccessor_X_To(&acc);
			return acc;
		}

		void AssignAccessor_Y_To(VirtArrayAccessor_1D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nofSteps_Y, m_nStepSize_Y);
		}

		VirtArrayAccessor_1D<T> GenAccessor_Y() const
		{
			VirtArrayAccessor_1D<T> acc;
			AssignAccessor_Y_To(&acc);
			return acc;
		}

		void CopyTo(VirtArrayAccessor_2D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nofSteps_X, m_nStepSize_X, m_nofSteps_Y, m_nStepSize_Y);
		}

		VirtArrayAccessor_2D<T> Clone() const
		{
			VirtArrayAccessor_2D<T> arr;
			CopyTo(&arr);
			return arr;
		}

		void AssignTransposeTo(VirtArrayAccessor_2D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nofSteps_Y, m_nStepSize_Y, m_nofSteps_X, m_nStepSize_X);
		}

		VirtArrayAccessor_2D<T> GenTranspose() const
		{
			VirtArrayAccessor_2D<T> acc;
			AssignTransposeTo(&acc);
			return acc;
		}

		void TransposeSelf()
		{
			VirtArrayAccessor_2D acc;
			AssignTransposeTo(&acc);
			acc.CopyTo(this);
		}

	protected:

		T * m_data;

		int m_nStepSize_X;
		int m_nofSteps_X;

		int m_nStepSize_Y;
		int m_nofSteps_Y;
	};

}