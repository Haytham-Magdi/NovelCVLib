#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>
#include <NovelCVLib\Common\ObjRef.h>
#include <NovelCVLib\Ncpp\Common\OffsetCalc_2D.h>
#include <NovelCVLib\Ncpp\Common\MemSimpleAccessor_2D.h>


namespace Ncpp
{
	//template<class T>
	//class MemAccessor_2D;
	//#define MemAccessor_2D_REF(T) Ncpp::ObjRef<Ncv::MemAccessor_2D<T>>
#define MemAccessor_2D_REF(T) ObjRef<MemAccessor_2D<T>>

	template<class T>
	class MemAccessor_2D : public Ncpp::Object
	{
	public:

		MemAccessor_2D(T * a_data, OffsetCalc_2D_Ref a_offsetCalc)
		{
			m_isLocked = false;
			Init(a_data, a_offsetCalc);
		}

		MemAccessor_2D_REF(T) Clone()
		{
			MemAccessor_2D_REF(T) pRet = new MemAccessor_2D<T>();

			pRet->m_data = m_data;
			pRet->m_data_Org = m_data_Org;

			pRet->m_offsetCalc = m_offsetCalc->Clone();
			pRet->m_offsetCalc->Lock();

			pRet->m_isLocked = false;
			return pRet;
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

		int GetIndexSize_X()
		{
			return m_offsetCalc->GetOffsetCalc_X()->GetIndexSize();
		}

		int GetIndexSize_Y()
		{
			return m_offsetCalc->GetOffsetCalc_Y()->GetIndexSize();
		}

		int GetIndexSize_X_Org()
		{
			return m_offsetCalc->GetOffsetCalc_X_Org()->GetIndexSize();
		}

		int GetIndexSize_Y_Org()
		{
			return m_offsetCalc->GetOffsetCalc_Y_Org()->GetIndexSize();
		}

		OffsetCalc_2D_Ref GetOffsetCalc()
		{
			return m_offsetCalc;
		}

		MemAccessor_1D_REF(T) GenAccessor_1D_X()
		{
			return new MemAccessor_1D<T>(
				m_data, m_offsetCalc->GetOffsetCalc_X());
		}

		MemAccessor_1D_REF(T) GenAccessor_1D_Y()
		{
			return new MemAccessor_1D<T>(
				m_data, m_offsetCalc->GetOffsetCalc_Y());
		}

		MemSimpleAccessor_2D<T> GenSimpleAccessor()
		{
			MemSimpleAccessor_2D<T> sac;

			sac.Init(m_data + m_offsetCalc->GetOffsetPart1(), GetIndexSize_X(), GetIndexSize_Y(), 
				m_offsetCalc->GetOffsetCalc_X()->GetActualStepSize(),
				m_offsetCalc->GetOffsetCalc_Y()->GetActualStepSize()
				);

			return sac;
		}


		//void GenSimpleAccessor(MemSimpleAccessor_2D<T> * a_pSac)
		//{
		//	a_pSac->Init(m_data + m_offsetCalc->GetOffsetPart1(), 
		//		m_offsetCalc->GetOffsetCalc_X()->GetActualStepSize(),
		//		m_offsetCalc->GetOffsetCalc_Y()->GetActualStepSize()
		//		);
		//}

		void SetRange_Relative(int a_nBgn_X, int a_nEnd_X, int a_nBgn_Y, int a_nEnd_Y)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_offsetCalc->Unlock();
			m_offsetCalc->SetRange_Relative(a_nBgn_X, a_nEnd_X, a_nBgn_Y, a_nEnd_Y);
			m_offsetCalc->Lock();
		}

		void SetRange_Relative_X(int a_nBgn_X, int a_nEnd_X)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_offsetCalc->Unlock();
			m_offsetCalc->SetRange_Relative_X(a_nBgn_X, a_nEnd_X);
			m_offsetCalc->Lock();
		}

		void SetRange_Relative_Y(int a_nBgn_Y, int a_nEnd_Y)
		{
			if (m_isLocked)
				throw "m_isLocked";

			m_offsetCalc->Unlock();
			m_offsetCalc->SetRange_Relative_Y(a_nBgn_Y, a_nEnd_Y);
			m_offsetCalc->Lock();
		}

		void SwitchXY()
		{
			m_offsetCalc->Unlock();
			m_offsetCalc->SwitchXY();
			m_offsetCalc->Lock();
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

		MemAccessor_2D()
		{
			m_isLocked = false;
		}

		void Init(T * a_data, OffsetCalc_2D_Ref a_offsetCalc)
		{
			if (m_isLocked)
				throw "m_isLocked";

			Ncpp_ASSERT(nullptr != a_data);

			m_data = a_data;
			m_data_Org = a_data;

			m_offsetCalc = a_offsetCalc->Clone();
			m_offsetCalc->Lock();
		}

	protected:

		T * m_data;
		T * m_data_Org;
		OffsetCalc_2D_Ref m_offsetCalc;
		bool m_isLocked;
	};

}