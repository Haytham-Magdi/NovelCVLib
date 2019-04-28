#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>



#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncpp\Common\FixedCapacityVectorAccessor.h>

namespace Ncpp
{

	template<class T, int Capacity>
	class StaticAllocMem 
	{
	public:


		T * GetHeadPtr() const
		{
			return m_data;
		}

		int GetCapacity() const
		{
			return Capacity;
		}

		void InitAccessor(FixedCapacityVectorAccessor<T> * a_pAccessor)
		{
			a_pAccessor->Init(m_data, Capacity);
		}
	
	protected:

		T m_data[Capacity];
	};



}