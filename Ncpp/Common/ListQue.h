#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class ListQue : public Ncpp::Object
	{
	protected:

	public:

		ListQue()
		{
			m_pushPtr = nullptr;
			m_popPtr = nullptr;
		}

		void PushPtr(T * a_ptr)
		{
			Ncpp_ASSERT(nullptr != a_ptr);

			T * pOld = m_pushPtr; 

			if(nullptr != pOld)
			{
				pOld->pPrev = a_ptr;
				m_pushPtr = a_ptr;
			}
			else
			{
				m_pushPtr = a_ptr;
				m_popPtr = a_ptr;
			}
		}

		T * PopPtr()
		{
			T * ptr = m_popPtr;

			if(nullptr != ptr)
			{
				if(ptr != ptr->pPrev)
				{
					m_popPtr = ptr->pPrev;
					ptr->pPrev = ptr;
				}
				else
				{
					m_pushPtr = nullptr;
					m_popPtr = nullptr;
				}
			}

			return ptr;
		}

	protected:

		T * m_pushPtr;
		T * m_popPtr;
	};



}