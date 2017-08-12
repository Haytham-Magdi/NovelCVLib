#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\multilistque.h>


namespace Ncpp
{

	template<class T>
	class MultiListQueMgr
	{
	public:

		MultiListQueMgr()
		{
			m_nLastMinIndex = 0;
			m_nLastMaxIndex = 0;
		}

		void InitSize(int a_nSiz)
		{
			m_multiQues.Init(a_nSiz);
		}

		int GetNofQues()
		{
			return m_multiQues.GetNofQues();
		}

		T * PopPtrMin()
		{
			T * pLA = m_multiQues.PopPtr( m_nLastMinIndex );

			while( nullptr == pLA )
			{
				if(m_nLastMinIndex < m_nLastMaxIndex)
				{
					m_nLastMinIndex++;
					pLA = m_multiQues.PopPtr( m_nLastMinIndex );
				}
				else
				{
					break;
				}
			}

			return pLA;
		}

		T * PopPtrMax()
		{
			T * pLA = m_multiQues.PopPtr( m_nLastMaxIndex );

			while( nullptr == pLA )
			{
				if(m_nLastMaxIndex > m_nLastMinIndex)
				{
					m_nLastMaxIndex--;
					pLA = m_multiQues.PopPtr( m_nLastMaxIndex );
				}
				else
				{
					break;
				}
			}

			return pLA;
		}   

		void PushPtr(int a_nIndex, T * a_pLA)
		{
			Ncpp_ASSERT( a_nIndex >= 0 );

			m_multiQues.PushPtr(a_nIndex, a_pLA);

			if(a_nIndex < m_nLastMinIndex)
				m_nLastMinIndex = a_nIndex;

			if(a_nIndex > m_nLastMaxIndex)
				m_nLastMaxIndex = a_nIndex;

		}			

		int GetLastMinIndex()
		{
			return m_nLastMinIndex;
		}

		int GetLastMaxIndex()
		{
			return m_nLastMaxIndex;
		}

		int Get_CurMinIndex()
		{
			int i = m_nLastMinIndex;

			while( ! m_multiQues.IndexHasValue( i ) )
			{
				if( i >= m_nLastMaxIndex )
				{
					break;
				}

				i++;
			}

			m_nLastMinIndex = i;

			return i;
		}

		int Get_CurMaxIndex()
		{
			int i = m_nLastMaxIndex;

			while( ! m_multiQues.IndexHasValue( i ) )
			{
				if( i <= m_nLastMinIndex )
				{
					break;
				}

				i--;
			}

			m_nLastMaxIndex = i;

			return i;
		}




	protected:

		MultiListQue< T > m_multiQues;

		int m_nLastMinIndex;
		int m_nLastMaxIndex;
	};





}