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

		static void Add(S32Point & a_inp1, S32Point & a_inp2, S32Point * a_pOut)
		{
			a_pOut->x = a_inp1.x + a_inp2.x;
			a_pOut->y = a_inp1.y + a_inp2.y;
		}

		static S32Point Add(S32Point & a_inp1, S32Point & a_inp2)
		{
			S32Point ret;
			
			Add(a_inp1, a_inp2, &ret);
			return ret;
		}

		static void Subtract(S32Point & a_inp1, S32Point & a_inp2, S32Point * a_pOut)
		{
			a_pOut->x = a_inp1.x - a_inp2.x;
			a_pOut->y = a_inp1.y - a_inp2.y;
		}

		static S32Point Subtract(S32Point & a_inp1, S32Point & a_inp2)
		{
			S32Point ret;

			Subtract(a_inp1, a_inp2, &ret);
			return ret;
		}


		static void DivideByNum(const S32Point & a_inp, const float a_num, S32Point * a_pOut)
		{
			a_pOut->x = a_inp.x / a_num;
			a_pOut->y = a_inp.y / a_num;
		}

		static S32Point DivideByNum(const S32Point & a_inp, const float a_num)
		{
			S32Point ret;

			DivideByNum(a_inp, a_num, &ret);
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