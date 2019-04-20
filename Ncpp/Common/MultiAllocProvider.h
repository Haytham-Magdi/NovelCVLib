#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\Ncpp\Common\ArrayHolder_1D.h>

//#include <vector>


//namespace Ncv
namespace Ncpp
{
	//using namespace Ncpp;

	//template<class T>
	//class MultiAllocProvider;


	template<class T>
	class MultiAllocProvider : public Ncpp::Object
	{
	public:

		MultiAllocProvider(const int a_firstAllocVectorCapacity, const int a_anyOtherAllocVectorCapacity = a_firstAllocVectorCapacity,
			const int a_vectorOfAllocVectorsCapacity = 3000)
		{
			m_vectOfAllocVectors.SetCapacity(a_vectorOfAllocVectorsCapacity);
			AddNewAllocVector(a_firstAllocVectorCapacity);

			m_anyOtherAllocVectorCapacity = a_anyOtherAllocVectorCapacity;		
		}

		//T & ProvideNewElement()
		T * ProvideNewElementPtr()
		{
			if (!GetLastAllocVectPtr()->HasFreeCapacity())
			{
				AddNewAllocVector(m_anyOtherAllocVectorCapacity);
			}

			GetLastAllocVectPtr()->IncSize();
			return &GetLastAllocVectPtr()->GetBack();
		}

		int GetNofAllocVectors()
		{
			return m_vectOfAllocVectors.GetSize();
		}

		FixedVector<T> * GetAllocVectorPtrAt(int a_index)
		{
			return m_vectOfAllocVectors.GetAt(a_index);
		}

		~MultiAllocProvider()
		{
			for (int i = 0; i < m_vectOfAllocVectors.GetSize(); i++)
			{
				FixedVector<T> * vectPtr = m_vectOfAllocVectors.GetAt(i);
				delete vectPtr;
			}
		}

	protected:

		void AddNewAllocVector(const int a_newVectorCapacity)
		{
			m_pLastAllocVect = new FixedVector<T>(a_newVectorCapacity);
			m_vectOfAllocVectors.PushBack(m_pLastAllocVect);
		}

		FixedVector<T> * GetLastAllocVectPtr()
		{
			return m_pLastAllocVect;
		}

	protected:

		FixedVector< FixedVector<T> * > m_vectOfAllocVectors;
		FixedVector<T> * m_pLastAllocVect;

		int m_anyOtherAllocVectorCapacity;
	};

	template<class T>
	using MultiAllocProviderRef = ObjRef< MultiAllocProvider< T >>;

}


