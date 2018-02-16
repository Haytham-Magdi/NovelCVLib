#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolder_1D.h>

#include <vector>


namespace Ncv
{
	using namespace Ncpp;

	template<class T>
	class SimpleArrayHolder_1D;


//#define SimpleArrayHolder_1D_REF(T) ObjRef< SimpleArrayHolder_1D< T >>

	template<class T>
	class SimpleArrayHolder_1D : public ArrayHolder_1D<T>
	{
	public:

		SimpleArrayHolder_1D(int a_size)
		{
			m_allocVect.SetSize(a_size);
			m_actualAccessor.Init(m_allocVect.GetHeadPtr(), a_size);
			m_actualAccessor.AssignVirtAccessorTo(&m_virtAccessor);
		}

	protected:

		FixedVector<T> m_allocVect;
	};

	template<class T>
	using SimpleArrayHolder_1D_Ref = ObjRef< SimpleArrayHolder_1D< T >>;

}