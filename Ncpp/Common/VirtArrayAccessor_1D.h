#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\PtrIterator2.h>


namespace Ncpp
{
	template<class T>
	class VirtArrayAccessor_1D
	{
	public:

		VirtArrayAccessor_1D()
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

		
		void AssignPtrIteratorTo(PtrIterator2<T> * a_pItr)
		{
			AssignPtrIteratorTo(a_pItr, 0, (m_nofSteps - 1));
			//a_pAcc->Init(m_data, &m_data[(m_nofSteps - 1) * m_nStepSize], m_nStepSize);
		}

		void AssignPtrIteratorTo(PtrIterator2<T> * a_pItr, int a_bgnPos, int a_endPos)
		{
			a_pAcc->Init(&m_data[a_bgnPos * m_nStepSize], &m_data[a_endPos * m_nStepSize], m_nStepSize);
		}

		PtrIterator2<T> GenPtrIterator()
		{
			PtrIterator2<T> itr;
			itr.AssignPtrIteratorTo(&itr);
			return itr;
		}

		PtrIterator2<T> GenPtrIterator(int a_bgnPos, int a_endPos)
		{
			PtrIterator2<T> itr;
			itr.AssignPtrIteratorTo(&itr, a_bgnPos, a_endPos);
			return itr;
		}

		void CopyTo(VirtArrayAccessor_1D * a_pArr)
		{
			a_pArr->Init(m_data, m_nofSteps, m_nStepSize);
		}

		VirtArrayAccessor_1D Clone()
		{
			VirtArrayAccessor_1D arr;
			CopyTo(&arr);
			return arr;
		}

	protected:

		T * m_data;
		int m_nStepSize;
		int m_nofSteps;
	};
	
}