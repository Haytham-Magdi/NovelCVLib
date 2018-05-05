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

		int GetX() const
		{
			return sizeX;
		}

		int GetY() const
		{
			return sizeY;
		}

		void SetX(const int a_sizeX)
		{
			 sizeX = a_sizeX;
		}

		void SetY(const int a_sizeY)
		{
			sizeY = a_sizeY;
		}


		int CalcSize_1D() const
		{
			return sizeX * sizeY;
		}

	protected:

		int sizeX;
		int sizeY;
	};

}