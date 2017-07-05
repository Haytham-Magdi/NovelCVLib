#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <Novel-Lib\Ncpp\Common\Debug.h>


namespace Ncpp
{
	template<class T>
	class Range
	{
	public:

		Range()
		{
		}

		void Init(T a_bgn, T a_end)
		{
			//Ncpp_ASSERT(a_end);

			m_bgn = a_bgn;
			m_end = a_end;
		}

		static Range New(T a_bgn, T a_end)
		{
			Range ret;
			ret.Init(a_bgn, a_end);

			return ret;
		}

		T GetBgn()
		{
			return m_bgn;
		}

		T GetEnd()
		{
			return m_end;
		}

	protected:

		T m_bgn;
		T m_end;
	};
	
	//class IntRange : public Range<int>
	//{
	//public:
	//	int GetLength()
	//	{
	//		return 
	//	}
	//};

}