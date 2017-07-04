#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <Lib\Novel\Ncpp\Common\Debug.h>
//#include <Lib\Novel\Ncpp\Common\ListQue.h>
#include <Lib\Novel\Ncpp\Common\FixedVector.h>

#include <Lib\Novel\Ncpp\Common\FixedDeque.h>

namespace Ncpp
{
	template<class T>
	class PtrPrvider : FRM_Object
	{
	protected:

	public:

		void Init(int a_nSize)
		{
			m_allocVect.SetSize( a_nSize );

			m_ptrQue.SetCapacity( a_nSize );

			for( int i=0; i < a_nSize; i++ )
				m_ptrQue.PushBack( & m_allocVect[ i ] );
		}

		int GetNofAllocPtrs(void)
		{
			return m_allocVect.GetSize();
		}

		int GetNofAvlPtrs(void)
		{
			return m_ptrQue.GetSize();
		}

		void TakePtrBack( T * a_ptr )
		{
			m_ptrQue.PushBack();
		}

		T * ProvidePtr( )
		{
			T * ptr = m_ptrQue.GetFront();

			m_ptrQue.PopFront();

			return ptr;
		}

		FixedVector< T > & GetAllocArr()
		{
			return m_allocVect;
		}


	protected:

		FixedVector< T > m_allocVect;
		FixedDeque< T *> m_ptrQue;
	};


}