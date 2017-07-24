#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Ncpp\Common\FixedVector.h>

#include <NovelCVLib\Ncpp\Common\Debug.h>
//#include <NovelCVLib\Ncpp\Common\indexcalc.h>




namespace Ncpp
{
	template< class T >
	class CommonArrCollBuff : public Ncpp::Object
	{
	public :

		CommonArrCollBuff()
		{
			
		}

		~CommonArrCollBuff()
		{
			
		}

		CommonArrCollBuff( int a_nCommonCap, int a_nMaxNofArrs )
		{
			SetCapacity( a_nCommonCap, a_nMaxNofArrs );
		}

		void SetCapacity( int a_nCommonCap, int a_nMaxNofArrs )
		{
			m_buffArr.SetCapacity( a_nCommonCap );

			m_headArr.SetCapacity( a_nMaxNofArrs );
			m_sizeArr.SetCapacity( a_nMaxNofArrs );
		}

		void AddArr( int a_nSize )
		{
			m_headArr.PushBack(
				//& m_buffArr.GetBack() );
				& m_buffArr[ m_buffArr.GetSize() ] );
			
			m_sizeArr.PushBack( a_nSize );

			m_buffArr.IncSize( a_nSize );
		}

		void Reset()
		{
			m_buffArr.ResetSize();

			m_headArr.ResetSize();
			m_sizeArr.ResetSize();
		}

		T * GetHeadAt( int a_nIndex )
		{
			return m_headArr[ a_nIndex ];
		}

		int GetSizeAt( int a_nIndex )
		{
			return m_sizeArr[ a_nIndex ];
		}

		int GetDataSizeTot()
		{
			return m_buffArr.GetSize();
		}

		int GetNofHeads()
		{
			return m_headArr.GetSize();
		}


	protected:

		FixedVector< T > m_buffArr;

		FixedVector< T * > m_headArr;
		FixedVector< int > m_sizeArr;
	};

}
