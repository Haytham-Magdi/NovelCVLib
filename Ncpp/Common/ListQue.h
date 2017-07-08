#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class ListQue : FRM_Object
	{
	protected:

	public:

		ListQue()
		{
			m_pushPtr = NULL;
			m_popPtr = NULL;
		}

		void PushPtr(T * a_ptr)
		{
			Ncpp_ASSERT(NULL != a_ptr);

			T * pOld = m_pushPtr; 

			if(NULL != pOld)
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

			if(NULL != ptr)
			{
				if(ptr != ptr->pPrev)
				{
					m_popPtr = ptr->pPrev;
					ptr->pPrev = ptr;
				}
				else
				{
					m_pushPtr = NULL;
					m_popPtr = NULL;
				}
			}

			return ptr;
		}

	protected:

		T * m_pushPtr;
		T * m_popPtr;
	};



}