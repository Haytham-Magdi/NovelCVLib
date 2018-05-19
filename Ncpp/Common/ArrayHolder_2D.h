#pragma once

#include <NovelCVLib\Ncpp\Common\VirtArrayAccessor_2D.h>
#include <NovelCVLib\Ncpp\Common\ActualArrayAccessor_2D.h>



namespace Ncv
{
	using namespace Ncpp;

	template<class T>
	class ArrayHolder_2D;

	template<class T>
	using ArrayHolder_2D_Ref = ObjRef< ArrayHolder_2D< T >>;

	
	template<class T>
	class ArrayHolder_2D : public Ncpp::Object
	{
	public:

		//virtual ~ArrayHolder_2D() = 0;
		virtual ~ArrayHolder_2D() {}

		const VirtArrayAccessor_2D<T> & GetVirtAccessor() const
		//VirtArrayAccessor_2D<T> & GetVirtAccessor() const
		{
			return m_virtAccessor;
		}

		const ActualArrayAccessor_2D<T> & GetActualAccessor() const
		{
			return m_actualAccessor;
		}

		Size_2D GetActualSize() const
		{
			return m_actualAccessor.GetSize();
		}

		ArrayHolder_2D<T> * AsHolderPtr()
		{
			return this;
		}

		ArrayHolder_2D_Ref<T> AsHolderRef()
		{
			return this;
		}

		void TransposeVirtAccessor()
		{
			m_virtAccessor.TransposeSelf();
		}

	protected:

		VirtArrayAccessor_2D<T> m_virtAccessor;
		ActualArrayAccessor_2D<T> m_actualAccessor;
	};





}