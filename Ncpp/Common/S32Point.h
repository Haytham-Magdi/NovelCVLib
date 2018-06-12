#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncpp
{
	class S32Point // : public Ncpp::Object
	{
	public:

		S32Point()
		{
		}

		S32Point(int a_x, int a_y)
		{
			SetValue(a_x, a_y);
		}

		void SetValue(int a_x, int a_y)
		{
			x = a_x;
			y = a_y;
		}

		int GetX() const
		{
			return x;
		}

		int GetY() const
		{
			return y;
		}

		S32Point Clone() const
		{
			S32Point ret = *this;

			return ret;
		}

		//void SetX(const int a_sizeX)
		//{
		//	 x = a_sizeX;
		//}

		//void SetY(const int a_sizeY)
		//{
		//	y = a_sizeY;
		//}


	//protected:
	public:

		int x;
		int y;
	};

}