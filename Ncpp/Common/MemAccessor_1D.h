#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <Lib\Novel\Ncpp\Common\Debug.h>
#include <Lib\Novel\Ncpp\Common\OffsetCalc_1D.h>
#include <Lib\Novel\Ncpp\Common\PtrIterator.h>
#include <Lib\Novel\Ncpp\Common\MemSimpleAccessor_1D.h>


namespace Ncpp
{
#define MemAccessor_1D_REF(T) Ncpp::ObjRef< MemAccessor_1D< T > >

	template<class T>
	class MemAccessor_1D : FRM_Object
	{
	public:

		MemAccessor_1D(T * a_data, OffsetCalc_1D_Ref a_offsetCalc)
		{
			m_isLocked = false;
			Init(a_data, a_offsetCalc);
		}

		MemAccessor_1D_REF(T) Clone()
		{
			MemAccessor_1D_REF(T) pRet = new MemAccessor_1D<T>();

			pRet->m_data = m_data;
			pRet->m_data_Org = m_data_Org;

			pRet->m_offsetCalc = m_offsetCalc->Clone();
			pRet->m_offsetCalc->Lock();

			pRet->m_isLocked = false;
			return pRet;
		}

		int GetIndexSize()
		{
			return m_offsetCalc->GetIndexSize();
		}

		MemSimpleAccessor_1D<T> GenSimpleAccessor()
		{
			MemSimpleAccessor_1D<T> sac;

			sac.Init(m_data + m_offsetCalc->GetOffsetPart1(), GetIndexSize(),
				m_offsetCalc->GetActualStepSize());

			return sac;
		}

		PtrIterator<T> GenPtrIterator()
		{
			return GenPtrIterator(0, this->GetIndexSize() - 1);
		}

		PtrIterator<T> GenPtrIterator(int a_nBgn, int a_nEnd)
		{
			T * ptr_P2 = &(this->GetDataPtr())[m_offsetCalc->GetOffsetPart1()];

			T * ptr_Bgn = &ptr_P2[a_nBgn];
			T * ptr_End = &ptr_P2[m_offsetCalc->CalcPart2(a_nEnd)];

			PtrIterator<T> ret(ptr_Bgn, ptr_End, m_offsetCalc->GetActualStepSize());

			return ret;
		}

		bool IsLocked()
		{
			return m_isLocked;
		}

		void Lock()
		{
			m_isLocked = true;
		}

		void Unlock()
		{
			m_isLocked = false;
		}

		OffsetCalc_1D_Ref GetOffsetCalc()
		{
			return m_offsetCalc;
		}

		T * GetDataPtr()
		{
			return m_data;
		}

		T * GetDataPtr_Org()
		{
			return m_data_Org;
		}

		void SetDataPtr(T * a_data)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_data = a_data;
		}

	protected:

		MemAccessor_1D()
		{
			m_isLocked = false;
		}

		void Init(T * a_data, OffsetCalc_1D_Ref a_offsetCalc)
		{
			if (m_isLocked)
				throw "m_isLocked";

			Ncpp_ASSERT(NULL != a_data);

			m_data = a_data;
			m_data_Org = a_data;

			m_offsetCalc = a_offsetCalc->Clone();
			m_offsetCalc->Lock();
		}

	protected:

		T * m_data;
		T * m_data_Org;
		OffsetCalc_1D_Ref m_offsetCalc;
		bool m_isLocked;
	};

}