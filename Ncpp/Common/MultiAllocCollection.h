#pragma once

#include <NovelCVLib\Ncpp\Common\commonLib_Misc.h>
//#include <NovelCVLib\Ncpp\Common\ArrayHolder_1D.h>

//#include <vector>


namespace Ncv
{
	using namespace Ncpp;

	//template<class T>
	//class MultiAllocCollection;


	template<class T>
	class MultiAllocCollection : public Ncpp::Object
	{
	public:

		MultiAllocCollection()
		{
			m_vectOfAllocVectors.SetCapacity(3000);
			AddNewAllocVector();
		
		}

		T & ProvideNewElement()
		{
			if (!GetLastAllocVectPtr()->HasFreeCapacity())
			{
				AddNewAllocVector();
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
			return m_vectOfAllocVectors.GetAt();
		}

		~MultiAllocCollection()
		{
			for (int i = 0; i < m_vectOfAllocVectors.GetSize(); i++)
			{
				FixedVector<T> * vectPtr = &m_vectOfAllocVectors.GetAt(i);
				delete vectPtr;
			}
		}

	protected:

		void AddNewAllocVector()
		{
			m_pLastAllocVect = new FixedVector<T>(10000);
			m_vectOfAllocVectors.PushBack(m_pLastAllocVect);
		}

		FixedVector<T> * GetLastAllocVectPtr()
		{
			return m_pLastAllocVect;
		}

	protected:

		FixedVector< FixedVector<T> * > m_vectOfAllocVectors;
		FixedVector<T> * m_pLastAllocVect;
	};

	template<class T>
	using MultiAllocCollectionRef = ObjRef< MultiAllocCollection< T >>;

}


