#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolder_1D.h>

#include <vector>


namespace Ncv
{
	using namespace Ncpp;

	template<class T>
	class ArrayHolderProxy_1D;


#define ArrayHolderProxy_1D_REF(T) ObjRef< ArrayHolderProxy_1D< T >>

	template<class T>
	class ArrayHolderProxy_1D : public ArrayHolder_1D<T>
	{
	public:

		ArrayHolderProxy_1D(ArrayHolderProxy_1D_REF(T) a_orgHolder)
		{
			m_orgHolder = a_orgHolder;
			a_orgHolder->m_actualAccessor.CopyTo(&m_actualAccessor);
			a_orgHolder->m_virtAccessor.CopyTo(&m_virtAccessor);
		}

	protected:

		ArrayHolderProxy_1D_REF(T) m_orgHolder;
	};

}