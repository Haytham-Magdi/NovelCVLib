#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>



#include <Lib\Novel\Ncpp\Common\Debug.h>
#include <Lib\Novel\Ncpp\Common\Object.h>


namespace Ncpp
{
	//class FixedVector;

	class FixedVectorDebug
	{
	public:

		static int AllocCnt;
		static int AllocCnt_Old;

		static int AllocCnt_2;
		static int AllocCnt_2_Old;
		
		static int FixedVectorID;		

		static int * FixedVectorID_Arr;
		static int FixedVectorID_Arr_Size;

		static int * FixedVectorID_Cycle_Arr;
		static int CycleNum;

		static long long AllocSizeTot;
		static long long AllocSizeTot_Old;

		static int MaxID_Activated;


		static void Init()
		{
			if( NULL == FixedVectorDebug::FixedVectorID_Arr )
			{
				FixedVectorID_Arr = new int [ 
					FixedVectorID_Arr_Size ];

				FixedVectorID_Cycle_Arr = new int [ 
					FixedVectorID_Arr_Size ];

				Reset_ID_Arr();

				for( int i=0; i < FixedVectorID_Arr_Size; i++ )
				{
					FixedVectorID_Cycle_Arr[ i ] = CycleNum;
				}

				
			}
		}


		static void Reset_ID_Arr()
		{
			Ncpp_ASSERT( NULL != FixedVectorDebug::FixedVectorID_Arr );

			for( int i=0; i < FixedVectorID_Arr_Size; i++ )
			{
				FixedVectorID_Arr[ i ] = -1;
			}

		}


		static void ActivateID( int a_nID ) 
		{
			return;

			//if( 931 == a_nID )
			//if( 13648 == a_nID )
			if( 13649 == a_nID )
				a_nID = a_nID;

			Ncpp_ASSERT( a_nID < FixedVectorID_Arr_Size );

			Ncpp_ASSERT( -1 == FixedVectorID_Arr[ a_nID ] );

			if( a_nID > MaxID_Activated )
				MaxID_Activated = a_nID;

			FixedVectorID_Arr[ a_nID ] = 100;

			AllocCnt_2++;

			FixedVectorID_Cycle_Arr[ a_nID ] = CycleNum;
		}


		static void DeactivateID( int a_nID ) 
		{
			return;

			//if( 931 == a_nID )
			if( 13648 == a_nID )
				a_nID = a_nID;

			Ncpp_ASSERT( a_nID < FixedVectorID_Arr_Size );

			Ncpp_ASSERT( 100 == FixedVectorID_Arr[ a_nID ] );

			//if( CycleNum > 0 )
				Ncpp_ASSERT( CycleNum == FixedVectorID_Cycle_Arr[ a_nID ] );
				//Ncpp_ASSERT( CycleNum - 1 == FixedVectorID_Cycle_Arr[ a_nID ] );
				//Ncpp_ASSERT( CycleNum - 1 != FixedVectorID_Cycle_Arr[ a_nID ] );
			 
			FixedVectorID_Arr[ a_nID ] = -1;

			AllocCnt_2--;
		}


		static void IncCycleNum() 
		{
			int nActCnt = 0;

			int nDeactCnt = 0;

			for( int i=0; i < FixedVectorID_Arr_Size; i++ )
			{
				if( FixedVectorID_Cycle_Arr[ i ] >= CycleNum )				
				{
					if( -1 != FixedVectorID_Arr[ i ] )
					{
						nActCnt ++;

						i = i;
					}
					else
					{
						nDeactCnt ++;

						i = i;
					}
				}
			}


			int nSameCnt = 0;

			int nDifCnt = 0;

			for( int i=0; i < ObjectFriend::s_nTestBuf_Siz; i++ )
			{
				if( 0 == ObjectFriend::m_testBuf[ i ] )
					continue;

				int nVal_1 = ObjectFriend::m_testBuf[ i ];
				int nVal_2 = ObjectFriend::m_testBuf_2[ i ];

				if( nVal_1 == nVal_2 )
				{
					nSameCnt++;
				}
				else
				{
					nDifCnt++;
				}

			}


			CycleNum++;

			AllocCnt_Old = AllocCnt;
			
			AllocCnt_2_Old = AllocCnt_2;
			
			AllocSizeTot_Old = AllocSizeTot;
		}


		static void Update()
		{
			if( NULL != pFunc_Update )
				pFunc_Update();
		}

	//protected:

		static void (* pFunc_Update)();   

	};

	template<class T>
	class FixedVector : FRM_Object
	{
	public:
		//virtual T GetAt(int a_index) = 0;

		FixedVector() { Init(); }
		FixedVector( int a_capacity ) { Init(); SetCapacity( a_capacity ); }

		T * GetHeadPtr()
		{
			return m_data;
		}

		~FixedVector() 
		{
			if( NULL != m_data )
			{
				delete [] m_data;
				FixedVectorDebug::AllocCnt--;

				FixedVectorDebug::AllocSizeTot -= 
					m_capacity * sizeof( T );

				FixedVectorDebug::DeactivateID( m_id );

				FixedVectorDebug::Update();
			}

			int a = FixedVectorDebug::AllocCnt;

		}

		int GetSize() { return m_size; }

		void SetAllToVal( T a_val ) 
		{ 
			for( int i=0; i < m_size; i++ )
				m_data[ i ] = a_val;
		}

		void IncSize( int a_nInc = 1 ) 
		{ 
			Ncpp_ASSERT( m_size + a_nInc <= m_capacity );

			SetSize( GetSize() + a_nInc ); 
		}



		int GetCapacity( )
		{
			return m_capacity;
		}


		void SetCapacity( int a_capacity )
		{
			if( NULL != m_data )
			{
				delete [] m_data;
				FixedVectorDebug::AllocCnt--;

				FixedVectorDebug::AllocSizeTot -= 
					m_capacity * sizeof( T );

				FixedVectorDebug::DeactivateID( m_id );

				FixedVectorDebug::Update();
			}

			int a = FixedVectorDebug::AllocCnt;

			m_data = new T[a_capacity];
			FixedVectorDebug::AllocCnt++;

			a = FixedVectorDebug::AllocCnt;

			m_capacity = a_capacity;
			m_size = 0;

			int nNewAllocSiz = m_capacity * sizeof( T );

			FixedVectorDebug::AllocSizeTot += 
				nNewAllocSiz;

			if( nNewAllocSiz > 10000000 )
				a = a;

			FixedVectorDebug::ActivateID( m_id );

			int a2 = FixedVectorDebug::AllocSizeTot;

			int a3 = m_capacity * sizeof( T );

			//if( FixedVectorDebug::AllocSizeTot > 400000000 )
			if( FixedVectorDebug::AllocSizeTot > 700000000 )
				a2 = a2;

			if( a3 > 100000000 )
				a2 = a2;


			FixedVectorDebug::Update();
		}

		T & operator[](int a_pos)
		{
			return m_data[a_pos];
		}

		T & GetAtBack(int a_nBackIndex)
		{
			return m_data[ m_size - 1 - a_nBackIndex ];
		}

		void ResetSize()
		{
			m_size = 0;
		}

		void SetSize( int a_size )
		{
			if( m_capacity < a_size )
				SetCapacity( a_size );

			m_size = a_size;
		}

		void PushBack( T a_val )
		{
			Ncpp_ASSERT( m_size < m_capacity );

			m_data[ m_size ] = a_val;
			m_size++;
		}

		T & GetBack()
		{
			return m_data[m_size - 1];
		}


	protected:

		void Init()
		{
			FixedVectorDebug::Init();

			m_data = NULL;
			m_size = 0;
			m_capacity = 0;

			m_id = FixedVectorDebug::FixedVectorID++;
		}

	protected:

		T * m_data;
		int m_size;
		int m_capacity;
		int m_id;
	};


	#define FixedVector_REF(T) Ncpp::ObjRef< FixedVector<T> >



}