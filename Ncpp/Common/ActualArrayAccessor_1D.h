#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_1D.h>
#include <NovelCVLib\Ncpp\Common\PtrIterator2.h>


namespace Ncpp
{
	template<class T>
	class ActualArrayAccessor_1D
	{
	public:

		ActualArrayAccessor_1D()
		{
		}

		void Init(T * a_data, int a_nSize)
		{
			Ncpp_ASSERT(a_nSize >= 0);

			m_data = a_data;
			m_nSize = a_nSize;
		}

		T & operator[](int a_pos) const
		{
			Ncpp_ASSERT(a_pos >= 0);
			Ncpp_ASSERT(a_pos < m_nSize);

			return m_data[a_pos];
		}

		T * GetData() const
		{
			return m_data;
		}

		int GetSize() const
		{
			return m_nSize;
		}

		void SetData(T * a_data)
		{
			m_data = a_data;
		}

		void SetSize(int a_nSize)
		{
			m_nSize = a_nSize;
		}

		void CopyTo(ActualArrayAccessor_1D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nSize);
		}

		ActualArrayAccessor_1D<T> Clone() const
		{
			ActualArrayAccessor_1D<T> acc;
			CopyTo(&acc);
			return acc;
		}

		void AssignVirtAccessorTo(VirtArrayAccessor_1D<T> * a_pAcc) const
		{
			a_pAcc->Init(m_data, m_nSize, 1);
		}

		VirtArrayAccessor_1D<T> GenVirtAccessor() const
		{
			VirtArrayAccessor_1D<T> acc;
			AssignVirtAccessorTo(&acc);
			return acc;
		}

		void AssignPtrIteratorTo(PtrIterator2<T> * a_pItr) const
		{
			AssignPtrIteratorTo(a_pItr, 0, (m_nSize - 1));
		}

		void AssignPtrIteratorTo(PtrIterator2<T> * a_pItr, int a_bgnPos, int a_endPos) const
		{
			Ncpp_ASSERT(a_bgnPos >= 0);
			Ncpp_ASSERT(a_bgnPos < m_nSize);

			Ncpp_ASSERT(a_endPos >= 0);
			Ncpp_ASSERT(a_endPos < m_nSize);

			a_pItr->Init(&m_data[a_bgnPos], &m_data[a_endPos], 1);
		}

		PtrIterator2<T> GenPtrIterator() const
		{
			PtrIterator2<T> itr;
			AssignPtrIteratorTo(&itr);
			return itr;
		}

		PtrIterator2<T> GenPtrIterator(int a_bgnPos, int a_endPos) const
		{
			PtrIterator2<T> itr;
			AssignPtrIteratorTo(&itr, a_bgnPos, a_endPos);
			return itr;
		}

	protected:

		T * m_data;
		int m_nSize;
	};

}