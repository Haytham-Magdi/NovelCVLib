#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
#include <NovelCVLib\Ncpp\Common\ArrayHolder_2D.h>
#include <NovelCVLib\Ncpp\Common\Size_2D.h>

#include <vector>


namespace Ncv
{
	using namespace Ncpp;

	//template<class T>
	//class ArrayHolderProxy_2D;


//#define ArrayHolderProxy_2D_REF(T) ObjRef< ArrayHolderProxy_2D< T >>

	template<class T>
	class ArrayHolderProxy_2D : public ArrayHolder_2D<T>
	{
	public:

		//ArrayHolderProxy_2D(ArrayHolderProxy_2D_REF(T) a_orgHolder)
		ArrayHolderProxy_2D(ArrayHolder_2D_Ref<T> a_orgHolder)
		{
			//throw "Not Implemented!";

			m_orgHolder = a_orgHolder;

			//a_orgHolder->m_actualAccessor.CopyTo(&m_actualAccessor);
			//a_orgHolder->m_virtAccessor.CopyTo(&m_virtAccessor);

			a_orgHolder->GetActualAccessor().CopyTo(&m_actualAccessor);
			a_orgHolder->GetVirtAccessor().CopyTo(&m_virtAccessor);

			//m_virtAccessor.Init(m_allocVect.GetHeadPtr(), a_size.GetX(), 1, a_size.GetY(), a_size.GetX());
			//m_actualAccessor.Init(m_allocVect.GetHeadPtr(), a_size.GetX(), a_size.GetY());
		}

	protected:

		ArrayHolder_2D_Ref<T> m_orgHolder;
	};

}