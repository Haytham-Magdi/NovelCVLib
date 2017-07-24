#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\ListQue.h>
#include <NovelCVLib\Ncpp\Common\FixedVector.h>


namespace Ncpp
{
	template<class T>
	class MultiListQue : public Ncpp::Object
	{
	protected:

	public:

		void Init(int a_nofQues)
		{
			m_pushVect.SetSize(a_nofQues);
			m_popVect.SetSize(a_nofQues);

			for(int i=0; i<a_nofQues; i++)
			{
				m_pushVect[i] = nullptr;
				m_popVect[i] = nullptr;
			}
		}

		int GetNofQues(void)
		{
			return m_pushVect.GetSize();
		}

		void PushPtr(int a_nIndex, T * a_ptr)
		{
			Ncpp_ASSERT(a_nIndex < m_pushVect.GetSize());
			Ncpp_ASSERT(nullptr != a_ptr);

			T * pOld = m_pushVect[a_nIndex]; 

			if(nullptr != pOld)
			{
				pOld->pPrev = a_ptr;
				m_pushVect[a_nIndex] = a_ptr;
			}
			else
			{
				m_pushVect[a_nIndex] = a_ptr;
				m_popVect[a_nIndex] = a_ptr;
			}
		}

		T * PopPtr(int a_nIndex)
		{
			Ncpp_ASSERT(a_nIndex < m_pushVect.GetSize());

			T * ptr = m_popVect[a_nIndex];

			if(nullptr != ptr)
			{
				if(ptr != ptr->pPrev)
				{
					m_popVect[a_nIndex] = ptr->pPrev;
					ptr->pPrev = ptr;
				}
				else
				{
					m_pushVect[a_nIndex] = nullptr;
					m_popVect[a_nIndex] = nullptr;
				}
			}

			return ptr;
		}

		bool IndexHasValue(int a_nIndex)
		{

			Ncpp_ASSERT(a_nIndex < m_pushVect.GetSize());

			T * ptr = m_popVect[a_nIndex];

			if(nullptr != ptr)
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		void PushQue(int a_nIndex, ListQue<T> * a_pQue)
		{
			T * ptr = a_pQue->PopPtr();

			while(nullptr != ptr)
			{
				this->PushPtr(a_nIndex, ptr);
				ptr = a_pQue->PopPtr();
			}
		}

		void PopToQue(int a_nIndex, ListQue<T> * a_pQue)
		{
			T * ptr = this->PopPtr(a_nIndex);

			while(nullptr != ptr)
			{
				a_pQue->PushPtr(ptr);
				ptr = this->PopPtr(a_nIndex);
			}
		}

	protected:

		FixedVector<T *> m_pushVect;
		FixedVector<T *> m_popVect;
	};



	template<class T>
	class MultiListQueMember
	{
	public:

		MultiListQueMember()
		{
			//pPrev = nullptr;
			pPrev = (T*)this;
		}

		friend class MultiListQue< T >;
		friend class ListQue< T >;
		

	private:

		T * pPrev;	//	for being ListQue Entry
	};


}