#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>


namespace Ncpp
{
	class Size_2D // : public Ncpp::Object
	{
	public:

		Size_2D()
		{
		}

		Size_2D(int a_nSizX, int a_nSizY)
		{
			Init(a_nSizX, a_nSizY);
		}

		void Init(int a_nSizX, int a_nSizY)
		{
			sizeX = a_nSizX;
			sizeY = a_nSizY;
		}

		//int Calc(int a_x, int a_y)
		//{
		//	return a_x + a_y * sizeX;
		//}

		//int Calc_X(int a_nIdx)
		//{
		//	return a_nIdx % sizeX;
		//}

		//int Calc_Y(int a_nIdx)
		//{
		//	return a_nIdx / sizeX;
		//}

		int GetX()
		{
			return sizeX;
		}

		int GetY()
		{
			return sizeY;
		}

		int CalcSize_1D()
		{
			return sizeX * sizeY;
		}

	protected:

		int sizeX;
		int sizeY;
	};

}