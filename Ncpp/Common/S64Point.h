#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>
#include <NovelCVLib\Ncpp\Common\S32Point.h>


namespace Ncpp
{
	class S64Point // : public Ncpp::Object
	{
	public:

		S64Point()
		{
		}

		S64Point(long long a_x, long long a_y)
		{
			SetValue(a_x, a_y);
		}

		void SetValue(long long a_x, long long a_y)
		{
			x = a_x;
			y = a_y;
		}

		long long GetX() const
		{
			return x;
		}

		long long GetY() const
		{
			return y;
		}

		S64Point Clone() const
		{
			S64Point ret = *this;

			return ret;
		}

		static void Add(S64Point & a_inp1, S64Point & a_inp2, S64Point * a_pOut)
		{
			a_pOut->x = a_inp1.x + a_inp2.x;
			a_pOut->y = a_inp1.y + a_inp2.y;
		}

		static S64Point Add(S64Point & a_inp1, S64Point & a_inp2)
		{
			S64Point ret;
			
			Add(a_inp1, a_inp2, &ret);
			return ret;
		}

		static void Subtract(S64Point & a_inp1, S64Point & a_inp2, S64Point * a_pOut)
		{
			a_pOut->x = a_inp1.x - a_inp2.x;
			a_pOut->y = a_inp1.y - a_inp2.y;
		}

		static S64Point Subtract(S64Point & a_inp1, S64Point & a_inp2)
		{
			S64Point ret;

			Subtract(a_inp1, a_inp2, &ret);
			return ret;
		}


		static void DivideByNum(const S64Point & a_inp, const float a_num, S64Point * a_pOut)
		{
			a_pOut->x = a_inp.x / a_num;
			a_pOut->y = a_inp.y / a_num;
		}

		static S64Point DivideByNum(const S64Point & a_inp, const float a_num)
		{
			S64Point ret;

			DivideByNum(a_inp, a_num, &ret);
			return ret;
		}

		S64Point DivideByNum(const float a_num)
		{
			const S64Point & a_inp = *this;

			return S64Point::DivideByNum(a_inp, a_num);
		}



		S32Point toS32Point()
		{
			const S64Point & src = *this;

			S32Point ret((int)src.x, (int)src.y);
			return ret;
		}



		//void SetX(const long long a_sizeX)
		//{
		//	 x = a_sizeX;
		//}

		//void SetY(const long long a_sizeY)
		//{
		//	y = a_sizeY;
		//}


	//protected:
	public:

		long long x;
		long long y;
	};

}