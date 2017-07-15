#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\ListQue.h>


namespace Ncpp
{
	template<class T>
	class APtrList : FRM_Object(APtrList<T>)
	{
	protected:

	public:

		APtrList()
		{
			m_lastPtr = NULL;
			m_firstPtr = NULL;
			m_currentPtr = NULL;
			m_nSize = 0;
		}

		int GetSize(void)
		{
			return m_nSize;
		}

		void PushLast(T * a_ptr)
		{
			if( ( (unsigned int)a_ptr & 0xff00fff0 ) == 0x02000040 )
				a_ptr = a_ptr;

			Ncpp_ASSERT(NULL != a_ptr);

			T * pOld = m_lastPtr; 

			if(NULL != pOld)
			{
				pOld->pPrev = a_ptr;
				a_ptr->pNext = pOld;
				m_lastPtr = a_ptr;
			}
			else
			{
				m_lastPtr = a_ptr;
				m_firstPtr = a_ptr;
			}

			m_nSize++;
		}

		T * PopFirst()
		{
			T * ptr = m_firstPtr;

			if(NULL != ptr)
				RemovePtr(ptr);

			return ptr;
		}


		void RemovePtr(T * a_ptr)
		{
			Ncpp_ASSERT(NULL != a_ptr);

			T * pCurrent = Current();

			if(1 == m_nSize)
			{
				m_lastPtr = NULL;
				m_firstPtr = NULL;
			}
			else if(a_ptr == m_lastPtr)
			{
				T * pNext = a_ptr->pNext;

				m_lastPtr = pNext;
				pNext->pPrev = pNext;
				a_ptr->pNext = a_ptr;
			}
			else if(a_ptr == m_firstPtr)
			{
				T * pPrev = a_ptr->pPrev;

				m_firstPtr = pPrev;
				pPrev->pNext = pPrev;
				a_ptr->pPrev = a_ptr;
			}
			else	//	Middle Position.
			{
				T * pNext = a_ptr->pNext;
				T * pPrev = a_ptr->pPrev;

				pPrev->pNext = pNext;
				pNext->pPrev = pPrev;

				a_ptr->pNext = a_ptr;
				a_ptr->pPrev = a_ptr;
			}

			m_nSize--;

			if( pCurrent == a_ptr )
				Last();
		}

		T * Current()
		{
			return m_currentPtr;
		}

		T * First()
		{
			m_currentPtr = m_firstPtr;
			return Current();
		}

		T * Last()
		{
			m_currentPtr = m_lastPtr;
			return Current();
		}

		T * Prev()
		{
			T * ptr = Current();

			if(NULL == ptr)
				return NULL;

			if( ptr == ptr->pPrev )
				return NULL;

			m_currentPtr = ptr->pPrev;

			return Current();
		}

		T * Next()
		{
			T * ptr = Current();

			if(NULL == ptr)
				return NULL;

			if( ptr == ptr->pNext )
				return NULL;

			m_currentPtr = ptr->pNext;

			return Current();
		}

		void TakeListElements( APtrList<T> & a_rSrc)
		{
			if( 0 == a_rSrc.GetSize() )
			{
				return;
			}
			else if( 0 == this->GetSize() )
			{
				m_lastPtr = a_rSrc.m_lastPtr;
				m_firstPtr = a_rSrc.m_firstPtr;
				m_nSize = a_rSrc.m_nSize;
			}
			else
			{
				T * oldLastPtr = m_lastPtr;

				m_lastPtr = a_rSrc.m_lastPtr;

				oldLastPtr->pPrev = a_rSrc.m_firstPtr;
				a_rSrc.m_firstPtr->pNext = oldLastPtr;

				m_nSize += a_rSrc.m_nSize;
			}

			a_rSrc.m_firstPtr = NULL;
			a_rSrc.m_lastPtr = NULL;
			a_rSrc.m_currentPtr = NULL;
			a_rSrc.m_nSize = 0;
		}


	protected:

		T * m_lastPtr;
		T * m_firstPtr;
		T * m_currentPtr;
		int m_nSize;
	};



}