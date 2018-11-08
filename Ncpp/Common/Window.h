#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Ncpp\Common\Range.h>


namespace Ncpp
{
	template<class T>
	class Window
	{
	public:

		Window()
		{
		}

		Window(T a_x1, T a_x2, T a_y1, T a_y2)
		{
			Init(a_x1, a_x2, a_y1, a_y2);
		}

		void Init(T a_x1, T a_x2, T a_y1, T a_y2)
		{
			m_x1 = a_x1;
			m_x2 = a_x2;

			m_y1 = a_y1;
			m_y2 = a_y2;
		}

		static Window New(T a_x1, T a_x2, T a_y1, T a_y2)
		{
			Window ret;
			ret.Init(a_x1, a_x2, a_y1, a_y2);

			return ret;
		}

		T GetX1() const
		{
			return m_x1;
		}

		T GetX2() const
		{
			return m_x2;
		}

		T GetY1() const
		{
			return m_y1;
		}

		T GetY2() const
		{
			return m_y2;
		}

		Range<T> GetRange_X() const
		{
			return Range<T>::New(m_x1, m_x2);
		}

		Range<T> GetRange_Y() const
		{
			return Range<T>::New(m_y1, m_y2);
		}

	protected:

		T m_x1;
		T m_x2;

		T m_y1;
		T m_y2;
	};
	
}