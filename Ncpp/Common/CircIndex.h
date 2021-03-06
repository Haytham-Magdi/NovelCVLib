#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>


namespace Ncpp
{
	class CircIndex : public Ncpp::Object
	{
	public :

		CircIndex(int a_nSize) : m_nSize(a_nSize)
		{
		}

		int Calc(int a_idx)
		{
			return (a_idx + m_nSize) % m_nSize;
		}

		int GetSize()
		{
			return m_nSize;
		}

	protected:

		const int m_nSize;
	};

}