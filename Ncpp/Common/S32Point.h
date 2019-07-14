#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>
#include <NovelCVLib\Common\Object.h>

#include <NovelCVLib\Ncpp\Common\Window.h>

#include <NovelCVLib\ElementOperations2\ElementOperations2.h>
#include <NovelCVLib\ElementOperations2\ElementOperations2_Int.h>

#include <NovelCVLib\Ncpp\Math\mathLib.h>



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

		void SetValue(const int a_x, const int a_y)
		{
			x = a_x;
			y = a_y;
		}

		//void SetValue(const F32Point & a_src)
		//{
		//	this->SetValue((int)a_src.x, (int)a_src.y);
		//}

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

		static void Subtract(const S32Point & a_inp1, const S32Point & a_inp2, S32Point * a_pOut)
		{
			a_pOut->x = a_inp1.x - a_inp2.x;
			a_pOut->y = a_inp1.y - a_inp2.y;
		}

		static S32Point Subtract(const S32Point & a_inp1, const S32Point & a_inp2)
		{
			S32Point ret;

			Subtract(a_inp1, a_inp2, &ret);
			return ret;
		}


		static void DivideByNum(const S32Point & a_inp, const float a_num, S32Point * a_pOut)
		{
			a_pOut->x = (int)(a_inp.x / a_num);
			a_pOut->y = (int)(a_inp.y / a_num);
		}

		static S32Point DivideByNum(const S32Point & a_inp, const float a_num)
		{
			S32Point ret;

			DivideByNum(a_inp, a_num, &ret);
			return ret;
		}

		static void SetToUndefined(S32Point * a_pArg)
		{
			Ncv::ElementOperations2::SetToUndefined(&a_pArg->x);
		}

		void SetToUndefined()
		{
			S32Point::SetToUndefined(this);
		}

		static bool IsUndefined(const S32Point & a_arg)
		{
			return Ncv::ElementOperations2::IsUndefined(a_arg.x);
		}

		bool IsUndefined() const
		{
			return S32Point::IsUndefined(*this);
		}

		bool IsInSize(const Size_2D a_siz) const
		{
			return 
				this->GetX() >= 0 &&
				this->GetX() < a_siz.GetX() &&
				this->GetY() >= 0 &&
				this->GetY() < a_siz.GetY();
		}

		bool IsInWindow(const Window<int> & a_window) const
		{
			return
				this->GetX() >= a_window.GetX1() &&
				this->GetX() <= a_window.GetX2() &&
				this->GetY() >= a_window.GetY1() &&
				this->GetY() <= a_window.GetY2();
		}

		static bool AreEqual(const S32Point & a_pnt1, const S32Point & a_pnt2)
		{
			return a_pnt1.GetX() == a_pnt2.GetX() &&
				a_pnt1.GetY() == a_pnt2.GetY();
		}




		//void SetX(const int a_sizeX)
		//{
		//	 x = a_sizeX;
		//}

		//void SetY(const int a_sizeY)
		//{
		//	y = a_sizeY;
		//}


		static int CalcMagSqr(const S32Point & a_arg)
		{
			return Math::Sqr(a_arg.x) + Math::Sqr(a_arg.y);
		}

		static float CalcMag(const S32Point & a_arg)
		{
			return sqrt((float)CalcMagSqr(a_arg));
		}

		int CalcMagSqr()
		{
			return S32Point::CalcMagSqr(*this);
		}

		float CalcMag()
		{
			return S32Point::CalcMag(*this);
		}


	//protected:
	public:

		int x;
		int y;
	};

}