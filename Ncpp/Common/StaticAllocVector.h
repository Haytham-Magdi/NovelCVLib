#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>



#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncpp
{

	template<class T, int Capacity>
	class StaticAllocVector 
	{
	public:

		StaticAllocVector()
		{
			m_size = 0;
		}


		T * GetHeadPtr() const
		{
			return m_data;
		}


		int GetSize() const { return m_size; }

		void SetAllToVal( const T & a_val ) 
		{ 
			for( int i=0; i < m_size; i++ )
				m_data[ i ] = a_val;
		}

		void IncSize( int a_nInc = 1 ) 
		{ 
			Ncpp_ASSERT( m_size + a_nInc <= Capacity );

			SetSize( GetSize() + a_nInc ); 
		}



		int GetCapacity() const
		{
			return Capacity;
		}

		bool HasFreeCapacity() const
		{
			return GetSize() < GetCapacity();
		}


		T & operator[](int a_pos) const
		{
			return GetAt(a_pos);
		}

		T & GetAt(int a_pos) const
		{
			Ncpp_ASSERT(a_pos >= 0 && a_pos < m_size);
			return m_data[a_pos];
		}

		T & GetAtBack(int a_nBackIndex) const
		{
			return GetAt(m_size - 1 - a_nBackIndex);
		}

		void ResetSize()
		{
			m_size = 0;
		}

		void SetSize( int a_size )
		{
			Ncpp_ASSERT(a_size >= 0);
			Ncpp_ASSERT(a_size <= Capacity);

			m_size = a_size;
		}

		void InitSize(int a_size)
		{
			SetSize(a_size);
		}

		void PushBack(const T & a_val)
		{
			Ncpp_ASSERT( m_size < Capacity );

			m_data[ m_size ] = a_val;
			m_size++;
		}

		T & GetBack() const
		{
			return GetAt(m_size - 1);
		}


	protected:

	
	protected:

		T m_data[Capacity];
		int m_size;
	};



}