#pragma once

#include <NovelCVLib\Common\commonLib.h>



namespace Ncv
{
	using namespace Ncpp;

	namespace ElementOperations2
	{

		template<class T>
		void AssertValue(const T & a_arg)
		{
			Ncpp::Exception::ThrowNotImplemented();

			//	to be revised
			throw "Not Implemented";

			////Hcpl_ASSERT(a_arg > -30000000.0f && arg < 30000000.0f);
			//Ncpp_ASSERT(a_arg > -30000000.0f);
		}


		template<class T>
		void Assign(T * a_pDest, const T & a_src)
		{
			AssertValue(a_src);
			*a_pDest = a_src;
		}


		template<class T>
		float CalcMagSqr(const T & a_arg)
		{
			AssertValue(a_arg);

			//return Sqr<T>(a_arg);
			return Sqr<float>((float)a_arg);
		}


		template<class T>
		float CalcMag(const T & a_arg)
		{
			AssertValue(a_arg);

			return sqrt((float)CalcMagSqr(a_arg));
		}

		template<class T>
		void CalcSqrVector(const T & a_inp, T * a_pOut)
		{
			AssertValue(a_inp);

			//*a_pOut = Sqr<float>((float)a_arg);
			Assign(a_pOut, Sqr<T>(a_arg));
		}


		template<class T>
		void Add(const T & a_inp1, const T & a_inp2, T * a_pOut)
		{
			AssertValue(a_inp1);
			AssertValue(a_inp2);

			Assign(a_pOut, a_inp1 + a_inp2);
		}


		template<class T>
		void IncBy(T & a_arg, const T & a_inc)
		{
			Add(a_arg, a_inc, &a_arg);
		}


		template<class T>
		void WaitedAdd(const T & a_inp1, const float a_weight1, const T & a_inp2, const float a_weight2, T * a_pOut)
		{
			AssertValue(a_inp1);
			AssertValue(a_inp2);

			AssertValue(a_weight1);
			AssertValue(a_weight2);

			T inp11, inp22;

			MultiplyByNum(a_inp1, a_weight1, &inp11);
			MultiplyByNum(a_inp2, a_weight2, &inp22);

			Add(inp11, inp22, a_pOut);
		}


		template<class T>
		void Subtract(const T & a_inp1, const T & a_inp2, T * a_pOut)
		{
			AssertValue(a_inp1);
			AssertValue(a_inp2);

			Assign(a_pOut, a_inp1 - a_inp2);
		}


		template<class T>
		void DecBy(T & a_arg, const T & a_dec)
		{
			Subtract(a_arg, a_dec, &a_arg);
		}


		template<class T>
		void DivideByNum(const T & a_inp, const float a_num, T * a_pOut)
		{
			AssertValue(a_inp);
			AssertValue(a_num);

			Assign(a_pOut, a_inp / a_num);

			//Assign(a_pOut, (float)(a_inp / a_num));
			//*a_pOut = (float)(a_inp / a_num);
		}


		template<class T>
		void DivideSelfByNum(T & a_arg, const float a_num)
		{
			DivideByNum(a_arg, a_num, &a_arg);
		}


		template<class T>
		void MultiplyByNum(const T & a_inp, const float a_num, T * a_pOut)
		{
			AssertValue(a_inp);
			AssertValue(a_num);

			Assign(a_pOut, a_inp * a_num);

			//Assign(a_pOut, (float)(a_inp * a_num));
			//*a_pOut = (float)(a_inp * a_num);
		}


		template<class T>
		void MultiplySelfByNum(T & a_arg, const float a_num)
		{
			MultiplyByNum(a_arg, a_num, &a_arg);
		}


		template<class T>
		void SetToZero(T * a_pArg)
		{
			*a_pArg = 0;
		}

		template<class T>
		T CreateZeroVal()
		{
			T val;
			SetToZero(&val);
			
			return val;
		}

		template<class T>
		bool IsUndefined(const T & a_arg)
		{
			Ncpp::Exception::ThrowNotImplemented();

			//	to be revised
			throw "Not Implemented";
		}


		template<class T>
		void SetToUndefined(T * a_pArg)
		{
			Exception::ThrowNotImplemented();
		}


		template<class T>
		void SetToBadValue(T * a_pArg)
		{
			Exception::ThrowNotImplemented();
		}


		template<class T>
		void AssertUndefinedOrValid(const T & a_arg)
		{
			if (IsUndefined(a_arg))
			{
				return;
			}
			AssertValue<T>(a_arg);
		}


		template<class T>
		float CalcStandev(const T & a_avg, const float a_avg_MagSqr)
		{
			AssertValue(a_avg);
			AssertValue(a_avg_MagSqr);

			float magSqr_Avg = CalcMagSqr(a_avg);

			float variance = a_avg_MagSqr - magSqr_Avg;

			//float standev = sqrt(fabs(variance));
			float standev;
			Assign(&standev, sqrt(fabs(variance)));

			return standev;
		}


		template<class T>
		//float CalcConflict(const T & a_avg_1, const float a_avg_MagSqr_1,
		bool CalcConflict(const T & a_avg_1, const float a_avg_MagSqr_1,
			const T & a_avg_2, const float a_avg_MagSqr_2)
		{
			AssertValue(a_avg_1);
			AssertValue(a_avg_MagSqr_1);
			AssertValue(a_avg_2);
			AssertValue(a_avg_MagSqr_2);

			T avg_12;
			Add(a_avg_1, a_avg_2, &avg_12);
			DivideSelfByNum(avg_12, 2);

			float avg_MagSqr_12 = (a_avg_MagSqr_1 + a_avg_MagSqr_2) / 2;

			float magSqr_Avg_1 = CalcMagSqr(a_avg_1);
			float magSqr_Avg_2 = CalcMagSqr(a_avg_2);
			float magSqr_Avg_12 = CalcMagSqr(avg_12);

			float standev_1 = CalcStandev(a_avg_1, a_avg_MagSqr_1);
			float standev_2 = CalcStandev(a_avg_2, a_avg_MagSqr_2);
			float standev_12 = CalcStandev(avg_12, avg_MagSqr_12);

			float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;

			//if (standev_12 > 20 && standev_12 > standev_MaxSide * 2)
			if (standev_12 > 30 && standev_12 > standev_MaxSide * 2)
			//if (standev_12 > 15 && standev_12 > standev_MaxSide * 2)
			//if (standev_12 > 15 && standev_12 > standev_MaxSide * 3)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		template<class T>
		bool CalcConflict2(const T & a_avg_1, const float a_avg_MagSqr_1, const float a_normStandev_1,
			const T & a_avg_2, const float a_avg_MagSqr_2, const float a_normStandev_2, const float a_normStandev_c)
		{
			AssertValue(a_avg_1);
			AssertValue(a_avg_MagSqr_1);
			AssertValue(a_normStandev_1);
			AssertValue(a_avg_2);
			AssertValue(a_avg_MagSqr_2);
			AssertValue(a_normStandev_2);
			AssertValue(a_normStandev_c);

			T avg_12;
			Add(a_avg_1, a_avg_2, &avg_12);
			DivideSelfByNum(avg_12, 2);

			float avg_MagSqr_12 = (a_avg_MagSqr_1 + a_avg_MagSqr_2) / 2;

			float magSqr_Avg_1 = CalcMagSqr(a_avg_1);
			float magSqr_Avg_2 = CalcMagSqr(a_avg_2);
			float magSqr_Avg_12 = CalcMagSqr(avg_12);

			float standev_1 = CalcStandev(a_avg_1, a_avg_MagSqr_1);
			float standev_2 = CalcStandev(a_avg_2, a_avg_MagSqr_2);
			float standev_12 = CalcStandev(avg_12, avg_MagSqr_12);

			float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;
			//float standev_MaxSide = (standev_1 > standev_2) ? standev_1 : standev_2;

			if (standev_12 > 20 && standev_12 > standev_MaxSide * 2
			//if (standev_12 > 30 && standev_12 > standev_MaxSide * 2
				//&& standev_12 > a_normStandev_1 * 3
				//&& standev_12 > a_normStandev_2 * 3
				//&& standev_12 > a_normStandev_c * 3
				)
				//if (standev_12 > 15 && standev_12 > standev_MaxSide * 2)
				//if (standev_12 > 15 && standev_12 > standev_MaxSide * 3)
			{
				if (!(
					standev_12 > a_normStandev_1 * 3
					&& standev_12 > a_normStandev_2 * 3
					//&& standev_12 > a_normStandev_c * 3
					))
				{
					return false;
				}

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class T>
		bool CalcThinConflict(
			const T & a_avg_1, const float a_avg_MagSqr_1, const float a_normStandev_1,
			const T & a_avg_2, const float a_avg_MagSqr_2, const float a_normStandev_2,
			const T & a_avg_c, const float a_avg_MagSqr_c, const float a_normStandev_c)
		{
			AssertValue(a_avg_1);
			AssertValue(a_avg_MagSqr_1);
			AssertValue(a_normStandev_1);
			AssertValue(a_avg_2);
			AssertValue(a_avg_MagSqr_2);
			AssertValue(a_normStandev_2);
			AssertValue(a_avg_c);
			AssertValue(a_avg_MagSqr_c);
			AssertValue(a_normStandev_c);

			//T avg_12;
			//Add(a_avg_1, a_avg_2, &avg_12);
			//DivideSelfByNum(avg_12, 2);

			T avg_1c;
			Add(a_avg_1, a_avg_c, &avg_1c);
			DivideSelfByNum(avg_1c, 2);

			T avg_2c;
			Add(a_avg_2, a_avg_c, &avg_2c);
			DivideSelfByNum(avg_2c, 2);

			float avg_MagSqr_1c = (a_avg_MagSqr_1 + a_avg_MagSqr_c) / 2;
			float avg_MagSqr_2c = (a_avg_MagSqr_2 + a_avg_MagSqr_c) / 2;

			float magSqr_Avg_1 = CalcMagSqr(a_avg_1);
			float magSqr_Avg_2 = CalcMagSqr(a_avg_2);
			
			float magSqr_Avg_1c = CalcMagSqr(avg_1c);
			float magSqr_Avg_2c = CalcMagSqr(avg_2c);

			float standev_1 = CalcStandev(a_avg_1, a_avg_MagSqr_1);
			float standev_2 = CalcStandev(a_avg_2, a_avg_MagSqr_2);
			
			float standev_1c = CalcStandev(avg_1c, avg_MagSqr_1c);
			float standev_2c = CalcStandev(avg_2c, avg_MagSqr_2c);




			if (standev_1c < 20 || standev_1c < standev_1 * 2)
				return false;

			if (standev_2c < 20 || standev_2c < standev_2 * 2)
				return false;

			if (
				standev_1c < a_normStandev_1 * 3
				&& a_normStandev_c < a_normStandev_1 * 3
				//|| standev_1c < a_normStandev_c * 3
				)
			{
				return false;
			}
			//else
			//{
			//	return true;
			//}

			if (
				standev_2c < a_normStandev_2 * 3
				&& a_normStandev_c < a_normStandev_2 * 3
				//|| standev_2c < a_normStandev_c * 3
				)
			{
				return false;
			}
			//else
			//{
			//	return true;
			//}


			return true;
		}


		template<class T>
		float Calc_ConflictDiff(const T & a_avg_1, const float a_avg_MagSqr_1,
			const T & a_avg_2, const float a_avg_MagSqr_2)
		{
			AssertValue(a_avg_1);
			AssertValue(a_avg_MagSqr_1);
			AssertValue(a_avg_2);
			AssertValue(a_avg_MagSqr_2);

			T avg_12;
			Add(a_avg_1, a_avg_2, &avg_12);
			DivideSelfByNum(avg_12, 2);

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


	}
}