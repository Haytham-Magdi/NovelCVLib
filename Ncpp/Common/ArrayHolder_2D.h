#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\CvIncludes.h>
#include <NovelCVLib\OpenCV\Types.h>
#include <NovelCVLib\OpenCV\error.h>
//#include <NovelCVLib\OpenCV\funcs1.h>
#include <vector>
//#include <NovelCVLib\OpenCV\Image.h>

//MemAccessor_2D


namespace Ncv
{
	using namespace Ncpp;

	template<class T>
	class ArrayHolder_2D;


#define ArrayHolder_2D_REF(T) ObjRef< ArrayHolder_2D< T >>

	template<class T>
	class ArrayHolder_2D : public Ncpp::Object
	{
	public:

		////ArrayHolder_2D(MemAccessor_2D_REF(T) a_memAccessor)
		//ArrayHolder_2D(OffsetCalc_2D_Ref a_offsetCalc)
		//{
		//	//int nSize_X = a_memAccessor->GetOffsetCalc()->GetOffsetCalc_X()->GetNofSteps();
		//	//int nSize_Y = a_memAccessor->GetOffsetCalc()->GetOffsetCalc_Y()->GetNofSteps();
		//	int nSize_X = a_offsetCalc->GetOffsetCalc_X_Org()->GetNofSteps();
		//	int nSize_Y = a_offsetCalc->GetOffsetCalc_Y_Org()->GetNofSteps();
		//	int nSize_1D = nSize_X * nSize_Y;

		//	m_allocVect = new FixedVector<T>();
		//	m_allocVect->SetSize(nSize_1D);

		//	OffsetCalc_2D_Ref offsetCalc = new OffsetCalc_2D(1, nSize_X, nSize_Y);
		//	//if (a_offsetCalc->GetOffsetCalc_X_Org()->GetNofSteps() != a_offsetCalc->GetOffsetCalc_X()->GetNofSteps())
		//	//if (a_offsetCalc->GetOffsetCalc_X_Org() != a_offsetCalc->GetOffsetCalc_X())
		//	//if ((int)a_offsetCalc->GetOffsetCalc_X_Org() != (int)a_offsetCalc->GetOffsetCalc_X())
		//	if (a_offsetCalc->GetOffsetCalc_X_Org()->GetActualStepSize() != a_offsetCalc->GetOffsetCalc_X()->GetActualStepSize())
		//	{
		//		offsetCalc->SwitchXY();
		//	}

		//	m_memAccessor = new MemAccessor_2D<T>(m_allocVect->GetHeadPtr(), offsetCalc);
		//	m_memAccessor->Lock();
		//}

		virtual ~ArrayHolder_2D() = 0;

		virtual ArrayHolder_2D_REF(T) Clone() = 0;

		//MemAccessor_2D_REF(T) GetMemAccessor()
		//{
		//	return m_memAccessor;
		//}

		//void SwitchXY()
		//{
		//	m_memAccessor->Unlock();
		//	m_memAccessor->SwitchXY();
		//	m_memAccessor->Lock();
		//}

		//int GetSize_1D()
		//{
		//	return m_memAccessor->GetNofSteps_X() * m_memAccessor->GetNofSteps_Y();
		//}

		//T * GetDataPtr()
		//{
		//	return m_memAccessor->GetDataPtr();
		//}


		VirtArrayAccessor_2D & GetAccessor()
		{
			return m_accessor;
		}

	protected:

		//ArrayHolder_2D_REF(T) Clone()
		//{
		//	ArrayHolder_2D_REF(T) ret = new ArrayHolder_2D<T>();

		//	if (a_bCloneData)
		//	{
		//		ret->m_allocVect = new FixedVector<T>();
		//		ret->m_allocVect->SetSize(m_allocVect->GetSize());

		//		memcpy(ret->m_allocVect->GetHeadPtr(), m_allocVect->GetHeadPtr(), m_allocVect->GetSize() * sizeof(T));
		//	}
		//	else
		//	{
		//		ret->m_allocVect = m_allocVect;
		//	}

		//	ret->m_memAccessor = m_memAccessor->Clone();
		//	ret->m_memAccessor->SetDataPtr(ret->m_allocVect->GetHeadPtr());
		//	ret->m_memAccessor->Lock();

		//	return ret;
		//}


	protected:

		ArrayHolder_2D()
		{

		}

	protected:

		VirtArrayAccessor_2D m_accessor;
		//FixedVector<T> m_allocVect;

		//MemAccessor_2D_REF(T) m_memAccessor;
		//FixedVector_REF(T) m_allocVect;
	};

}