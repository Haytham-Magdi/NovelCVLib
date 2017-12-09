#pragma once

#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_2D.h>
#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>



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

		virtual ~ArrayHolder_2D() = 0;
		virtual ArrayHolder_2D_REF(T) Clone() = 0;

		VirtArrayAccessor_2D & GetVirtAccessor()
		{
			return m_virtAccessor;
		}

		ActualArrayAccessor_2D & GetActualAccessor()
		{
			return m_actualAccessor;
		}

	protected:

		VirtArrayAccessor_2D m_virtAccessor;
		ActualArrayAccessor_2D m_actualAccessor;
	};

}