#pragma once

#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_1D.h>
#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_1D.h>



namespace Ncv
{
	using namespace Ncpp;

	template<class T>
	class ArrayHolder_1D;


//#define ArrayHolder_1D_REF(T) ObjRef< ArrayHolder_1D< T >>

	template<class T>
	class ArrayHolder_1D : public Ncpp::Object
	{
	public:

		virtual ~ArrayHolder_1D() = 0;

		const VirtArrayAccessor_1D & GetVirtAccessor() const
		//VirtArrayAccessor_1D & GetVirtAccessor() const
		{
			return m_virtAccessor;
		}

		const ActualArrayAccessor_1D & GetActualAccessor() const
		{
			return m_actualAccessor;
		}

		int GetSize() const
		{
			return m_actualAccessor.GetSize();
		}

	protected:

		VirtArrayAccessor_1D m_virtAccessor;
		ActualArrayAccessor_1D m_actualAccessor;
	};

	template<class T>
	using ArrayHolder_1D_Ref = ObjRef< ArrayHolder_1D< T >>;

}