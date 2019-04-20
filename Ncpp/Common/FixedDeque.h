#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>



#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncpp\Common\FixedVector.h>

namespace Ncpp
{
	template<class T>
	class FixedDeque : public Ncpp::Object
	{
	public:
		//virtual T GetAt(int a_index) = 0;

		FixedDeque() { Init(); }
		FixedDeque( int a_capacity ) { Init(); SetCapacity( a_capacity ); }

		~FixedDeque() 
		{
			if( nullptr != m_data )
			{
				delete [] m_data;

				FixedVectorDebug::AllocCnt--;

				FixedVectorDebug::AllocSizeTot -= 
					m_capacity * sizeof( T );

				FixedVectorDebug::DeactivateID( m_id );
			}
		}

		int GetSize() const { return m_size; }

		int GetCapacity() const { return m_capacity; }

		bool HasFreeCapacity() const
		{
			return GetSize() < GetCapacity();
		}

		void SetCapacity( int a_capacity )
		{
			if( nullptr != m_data )
			{
				delete [] m_data;

				FixedVectorDebug::AllocCnt--;

				FixedVectorDebug::AllocSizeTot -= 
					m_capacity * sizeof( T );

				FixedVectorDebug::DeactivateID( m_id );
			}

			m_data = new T[a_capacity];
			m_capacity = a_capacity;
			m_size = 0;

			FixedVectorDebug::AllocCnt++;

			FixedVectorDebug::AllocSizeTot += 
				m_capacity * sizeof( T );

			FixedVectorDebug::ActivateID( m_id );
		}

		T & operator[](int a_pos) const
		{
			int index = ( m_frontIdx + a_pos ) % m_capacity;
			return m_data[index];
		}

		T & GetAtRev(int a_pos) const
		{
			int index = ( m_frontIdx + m_size - 1 - a_pos ) % m_capacity;
			return m_data[index];
		}

		void ResetSize()
		{
			m_size = 0;
			//m_frontIdx = 0;
		}

		void PushBack( T a_val )
		{
			Ncpp_ASSERT( m_size < m_capacity );

			//if( ( m_frontIdx + m_size ) >= m_capacity )
			//	m_frontIdx = m_frontIdx ;


			int newIdx = ( m_frontIdx + m_size ) % m_capacity;

			//if( 64997 == newIdx )
			//	newIdx = newIdx;

			m_data[ newIdx ] = a_val;
			m_size++;
		}

		T & GetBack() const
		{
			int backIdx = ( m_frontIdx + m_size - 1 ) % m_capacity;
			return m_data[ backIdx ];
		}

		T & GetFront() const
		{
			//if( 64997 == m_frontIdx )
			//	m_frontIdx = m_frontIdx;

			return m_data[ m_frontIdx ];
		}

		void PopFront()
		{
			m_frontIdx = ( m_frontIdx + 1 ) % m_capacity;
			m_size--;
		}

	protected:

		void Init()
		{
			FixedVectorDebug::InitIfFirstTime();

			m_data = nullptr;
			m_size = 0;
			m_capacity = 0;

			m_frontIdx = 0;

			m_id = FixedVectorDebug::FixedVectorID++;
		}

	protected:

		T * m_data;
		int m_size;
		int m_frontIdx;
		int m_capacity;

		int m_id;
	};


	#define FixedDeque_REF(T) Ncpp::ObjRef< FixedDeque<T> >



}