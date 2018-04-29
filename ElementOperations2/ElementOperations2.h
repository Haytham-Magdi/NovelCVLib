#pragma once

#include <NovelCVLib\Common\commonLib.h>



namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{

		template<class T>
		void Assign(T * a_pDest, const T & a_src)
		{
			*a_pDest = a_src;
			//memcpy(a_pDest, &a_src, sizeof(T));
		}

		//template<class T>
		//void Copy_ByPtr(T * a_pDest, T * a_pSrc)
		//{
		//	memcpy(a_pDest, a_pSrc, sizeof(T));
		//}

		template<class T>
		float CalcMagSqr(const T & a_arg)
		{
			//return Sqr<T>(a_arg);
			return Sqr<float>((float)a_arg);
		}

		//template<class T>
		//float CalcMagSqr_ByPtr(T * a_pArg)
		//{
		//	//return Sqr<T>(*a_pArg);
		//	return Sqr<float>(*a_pArg);
		//}

		//template<class T>
		//void AssertValue_ByPtr(T * a_pArg)
		//{
		//	Ncpp_ASSERT(*a_pArg > -3000000.0f && *a_pArg < 3000000.0f);
		//}

		template<class T>
		float CalcMag(const T & a_arg)
		{
			return sqrt((float)CalcMagSqr_ByPtr(a_arg));
		}

		//template<class T>
		//float CalcMag_ByPtr(T * a_pArg)
		//{
		//	return sqrt((float)CalcMagSqr_ByPtr(a_pArg));
		//}

		template<class T>
		void Add(const T & a_inp1, const T & a_inp2, T * a_pOut)
		{
			*a_pOut = a_inp1 + a_inp2;
		}

		//template<class T>
		//void Add_ByPtr(T * a_pInp1, T * a_pInp2, T * a_pOut)
		//{
		//	*a_pOut = *a_pInp1 + *a_pInp2;
		//}

		template<class T>
		void WaitedAdd(const T & a_inp1, const float a_weight1, const T & a_inp2, const float a_weight2, T * a_pOut)
		{
			T inp11, inp22;

			MultiplyByNum_ByPtr(a_inp1, a_weight1, &inp11);
			MultiplyByNum_ByPtr(a_inp2, a_weight2, &inp22);

			Add(&inp11, &inp22, a_pOut);
		}

		//template<class T>
		//void WaitedAdd_ByPtr(T * a_pInp1, float a_weight1, T * a_pInp2, float a_weight2, T * a_pOut)
		//{
		//	T inp11, inp22;

		//	MultiplyByNum_ByPtr(a_pInp1, a_weight1, &inp11);
		//	MultiplyByNum_ByPtr(a_pInp2, a_weight2, &inp22);

		//	Add_ByPtr(&inp11, &inp22, a_pOut);
		//}

		template<class T>
		void Subtract(const T & a_inp1, const T & a_inp2, T * a_pOut)
		{
			*a_pOut = a_inp1 - a_inp2;
		}

		//template<class T>
		//void Subtract_ByPtr(T * a_pInp1, T * a_pInp2, T * a_pOut)
		//{
		//	*a_pOut = *a_pInp1 - *a_pInp2;
		//}

		template<class T>
		void DivideByNum(const T & a_inp, const float a_num, T * a_pOut)
		{
			*a_pOut = (float)(a_inp / a_num);
		}

		//template<class T>
		//void DivideByNum_ByPtr(T * a_pInp, const float a_num, T * a_pOut)
		//{
		//	*a_pOut = *a_pInp / a_num;
		//}

		template<class T>
		void MultiplyByNum(const T & a_inp, const float a_num, T * a_pOut)
		{
			*a_pOut = (float)(a_inp * a_num);
		}

		//template<class T>
		//void MultiplyByNum_ByPtr(T * a_pInp, const float a_num, T * a_pOut)
		//{
		//	*a_pOut = *a_pInp * a_num;
		//}

		template<class T>
		void SetToZero(T * a_pArg)
		{
			*a_pArg = 0;
		}

		//template<class T>
		//void SetToZero_ByPtr(T * a_pArg)
		//{
		//	*a_pArg = 0;
		//}

		template<class T>
		bool IsUndefined(const T & a_arg)
		{
			Ncpp::Exception::ThrowNotImplemented();

			//	to be revised
			throw "Not Implemented";
		}

		//template<class T>
		//bool IsUndefined_ByPtr(T * a_pArg)
		//{
		//	Ncpp::Exception::ThrowNotImplemented();

		//	//	to be revised
		//	throw "Not Implemented";
		//}

		template<class T>
		void SetToUndefined(T * a_pArg)
		{
			Exception::ThrowNotImplemented();
		}

		//template<class T>
		//void SetToUndefined_ByPtr(T * a_pArg)
		//{
		//	Exception::ThrowNotImplemented();
		//}

		template<class T>
		float CalcSqrt(const T * a_arg)
		{
			return sqrt((float)a_arg);
		}

		//template<class T>
		//float CalcSqrt_ByPtr(T * a_pArg)
		//{
		//	return sqrt((float)*a_pArg);
		//}

		template<class T>
		float CalcStandev(const T & a_avg, const float a_avg_MagSqr)
		{
			float magSqr_Avg = CalcMagSqr(a_avg);

			float variance = a_avg_MagSqr - magSqr_Avg;
			float standev = sqrt(fabs(variance));

			return standev;
		}

		//template<class T>
		//float CalcStandev_ByPtr(T * a_pAvg, float a_avg_MagSqr)
		//{
		//	float magSqr_Avg = CalcMagSqr_ByPtr(a_pAvg);

		//	float variance = a_avg_MagSqr - magSqr_Avg;
		//	float standev = sqrt(fabs(variance));

		//	return standev;
		//}

		template<class T>
		float CalcConflict(const T & a_avg_1, const float a_avg_MagSqr_1,
			const T & a_avg_2, const float a_avg_MagSqr_2)
		{
			T avg_12;
			Add(a_avg_1, a_avg_2, &avg_12);
			DivideByNum(avg_12, 2, &avg_12);

			float avg_MagSqr_12 = (a_avg_MagSqr_1 + a_avg_MagSqr_2) / 2;

			float magSqr_Avg_1 = CalcMagSqr(avg_1);
			float magSqr_Avg_2 = CalcMagSqr(avg_2);
			float magSqr_Avg_12 = CalcMagSqr(avg_12);

			float standev_1 = CalcStandev(avg_1, a_avg_MagSqr_1);
			float standev_2 = CalcStandev(avg_2, a_avg_MagSqr_2);
			float standev_12 = CalcStandev(avg_12, avg_MagSqr_12);

			float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;

			//if (standev_12 > 20 && standev_12 > standev_MaxSide * 2)
			//if (standev_12 > 15 && standev_12 > standev_MaxSide * 2)
			if (standev_12 > 15 && standev_12 > standev_MaxSide * 3)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		//template<class T>
		//float CalcConflict_ByPtr(T * a_pAvg_1, float a_avg_MagSqr_1,
		//	T * a_pAvg_2, float a_avg_MagSqr_2)
		//{
		//	T avg_12;
		//	Add_ByPtr(a_pAvg_1, a_pAvg_2, &avg_12);
		//	DivideByNum_ByPtr(&avg_12, 2, &avg_12);

		//	float avg_MagSqr_12 = (a_avg_MagSqr_1 + a_avg_MagSqr_2) / 2;

		//	float magSqr_Avg_1 = CalcMagSqr_ByPtr(a_pAvg_1);
		//	float magSqr_Avg_2 = CalcMagSqr_ByPtr(a_pAvg_2);
		//	float magSqr_Avg_12 = CalcMagSqr_ByPtr(&avg_12);

		//	float standev_1 = CalcStandev_ByPtr(a_pAvg_1, a_avg_MagSqr_1);
		//	float standev_2 = CalcStandev_ByPtr(a_pAvg_2, a_avg_MagSqr_2);
		//	float standev_12 = CalcStandev_ByPtr(&avg_12, avg_MagSqr_12);

		//	float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;

		//	//if (standev_12 > 20 && standev_12 > standev_MaxSide * 2)
		//	//if (standev_12 > 15 && standev_12 > standev_MaxSide * 2)
		//	if (standev_12 > 15 && standev_12 > standev_MaxSide * 3)
		//	{
		//		return true;
		//	}
		//	else
		//	{
		//		return false;
		//	}
		//}

		template<class T>
		float Calc_ConflictDiff(const T & a_avg_1, const float a_avg_MagSqr_1,
			const T & a_avg_2, const float a_avg_MagSqr_2)
		{
			T avg_12;
			Add(a_avg_1, a_avg_2, &avg_12);
			DivideByNum(avg_12, 2, &avg_12);

			float avg_MagSqr_12 = (a_avg_MagSqr_1 + a_avg_MagSqr_2) / 2;

			float magSqr_Avg_1 = CalcMagSqr(avg_1);
			float magSqr_Avg_2 = CalcMagSqr(avg_2);
			float magSqr_Avg_12 = CalcMagSqr(avg_12);

			float standev_1 = CalcStandev(avg_1, a_avg_MagSqr_1);
			float standev_2 = CalcStandev(avg_2, a_avg_MagSqr_2);
			float standev_12 = CalcStandev(avg_12, avg_MagSqr_12);

			float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;
			float ret = (standev_12 > standev_MaxSide) ? (standev_12 - standev_MaxSide) : 0;
			return ret;
		}

		//template<class T>
		//float Calc_ConflictDiff_ByPtr(T * a_pAvg_1, float a_avg_MagSqr_1,
		//	T * a_pAvg_2, float a_avg_MagSqr_2)
		//{
		//	T avg_12;

		//	Add_ByPtr(a_pAvg_1, a_pAvg_2, &avg_12);
		//	DivideByNum_ByPtr(&avg_12, 2, &avg_12);

		//	float avg_MagSqr_12 = (a_avg_MagSqr_1 + a_avg_MagSqr_2) / 2;

		//	float magSqr_Avg_1 = CalcMagSqr_ByPtr(a_pAvg_1);
		//	float magSqr_Avg_2 = CalcMagSqr_ByPtr(a_pAvg_2);
		//	float magSqr_Avg_12 = CalcMagSqr_ByPtr(&avg_12);

		//	float standev_1 = CalcStandev_ByPtr(a_pAvg_1, a_avg_MagSqr_1);
		//	float standev_2 = CalcStandev_ByPtr(a_pAvg_2, a_avg_MagSqr_2);
		//	float standev_12 = CalcStandev_ByPtr(&avg_12, avg_MagSqr_12);

		//	float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;
		//	float ret = (standev_12 > standev_MaxSide) ? (standev_12 - standev_MaxSide) : 0;

		//	return ret;
		//}

	}
}