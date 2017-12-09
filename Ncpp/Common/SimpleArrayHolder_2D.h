#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\OpenCV\Types.h>
//#include <NovelCVLib\OpenCV\error.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolder_2D.h>
#include <NovelCVLib\Ncpp\Common\Size_2D.h>

#include <vector>


namespace Ncv
{
	using namespace Ncpp;

	template<class T>
	class SimpleArrayHolder_2D;


#define SimpleArrayHolder_2D_REF(T) ObjRef< SimpleArrayHolder_2D< T >>

	template<class T>
	class SimpleArrayHolder_2D : public ArrayHolder_2D<T>
	{
	public:

		SimpleArrayHolder_2D(Size_2D & a_size)
		{
			m_allocVect.SetSize(a_size.CalcSize_1D());
			m_virtAccessor.Init(m_allocVect.GetHeadPtr(), a_size.GetX(), 1, a_size.GetY(), a_size.GetX());
			m_actualAccessor.Init(m_allocVect.GetHeadPtr(), a_size.GetX(), a_size.GetY());
		}

		virtual ArrayHolder_2D_REF(T) Clone()
		{
			ArrayHolder_2D_REF(T) ret = new SimpleArrayHolder_2D(m_accessor.GetSize());
		}

	protected:

		FixedVector<T> m_allocVect;
	};

}