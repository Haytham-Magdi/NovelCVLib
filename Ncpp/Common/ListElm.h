#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\Debug.h>
//#include <NovelCVLib\Ncpp\Common\ListQue.h>


namespace Ncpp
{
	template<class T>
	class ListElm : public Ncpp::Object
	{
	protected:

	public:

		ListElm()
		{
			m_pNext = nullptr;
			m_pPrev = nullptr;
		}

	public:

		ListElm< T > * GetNext()
		{
			return m_pNext;
		}

		ListElm< T > * GetPrev()
		{
			return m_pNext;
		}

		ListElm< T > * GetFarNext()
		{
			ListElm< T > * pNext = m_pNext;
			ListElm< T > * pOldNext = pNext;

			while( nullptr != pNext )
			{
				pOldNext = pNext;

				pNext = pNext->m_pNext;
			}

			return pOldNext;
		}

		ListElm< T > * GetFarPrev()
		{
			ListElm< T > * pPrev = m_pPrev;
			ListElm< T > * pOldPrev = pPrev;

			while( nullptr != pPrev )
			{
				pOldPrev = pPrev;

				pPrev = pPrev->m_pPrev;
			}

			return pOldPrev;
		}

		void AddNext( ListElm< T > * a_pElm )
		{
			Ncpp_ASSERT( nullptr == m_pNext );
			Ncpp_ASSERT( nullptr == a_pElm->m_pPrev );

			m_pNext = a_pElm;
			a_pElm->m_pPrev = this;
		}

		void AddPrev( ListElm< T > * a_pElm )
		{
			Ncpp_ASSERT( nullptr == m_pPrev );
			Ncpp_ASSERT( nullptr == a_pElm->m_pNext );

			m_pPrev = a_pElm;
			a_pElm->m_pNext = this;
		}

/*
		void InsertNext( ListElm< T > * a_pElm )
		{
			erwerwer
				BreakNext()
					BreakPrev()

			Ncpp_ASSERT( nullptr == m_pNext );
			Ncpp_ASSERT( nullptr == a_pElm->m_pPrev );

			m_pNext = a_pElm;
			a_pElm->m_pPrev = this;
		}
*/

		void BreakNext()
		{
			if( nullptr != m_pNext )
			{
				m_pNext->m_pPrev = nullptr;
				m_pNext = nullptr;
			}
		}

		void BreakPrev()
		{
			if( nullptr != m_pPrev )
			{
				m_pPrev->m_pNext = nullptr;
				m_pPrev = nullptr;
			}
		}

		void ConnectNextToPrev()
		{
			ListElm< T > * pNext = m_pNext;
			ListElm< T > * pPrev = m_pPrev;

			BreakNext();
			BreakPrev();

			if( nullptr != pNext &&
				nullptr != pPrev )
			{
				pPrev->AddNext( pNext );
			}
		}


		T Content;

	protected:

		ListElm< T > * m_pNext;
		ListElm< T > * m_pPrev;
	};



}