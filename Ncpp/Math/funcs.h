#pragma once


namespace Ncpp
{
	namespace Math
	{
		using namespace Ncpp;

		template<class T>
		inline T Sqr(T a_arg)
		{
			return a_arg * a_arg;
		}


		//float SomeFuncCP( float a_num_1, float a_num_2 )
		//{
		//	float res = fact( a_num_1 ) /
		//		( fact( a_num_2 ) * fact( a_num_1 - a_num_2 ) );
		//}


		template<class T>
		T SomeFuncCP_2( T a_num_1 )
		{
			T res = a_num_1 * ( a_num_1 - 1 ) / 2;

			return res;
		}

		int Round( float a_num );


		template<class T>
		void Min(const T & a_arg1, const T & a_arg2)
		{
			return (a_arg1 < a_arg2) ? a_arg1 : a_arg2;
		}

		template<class T>
		void MinOrEqual(const T & a_arg1, const T & a_arg2)
		{
			return (a_arg1 <= a_arg2) ? a_arg1 : a_arg2;
		}

		template<class T>
		void Max(const T & a_arg1, const T & a_arg2)
		{
			return (a_arg1 > a_arg2) ? a_arg1 : a_arg2;
		}

		template<class T>
		void MaxOrEqual(const T & a_arg1, const T & a_arg2)
		{
			return (a_arg1 >= a_arg2) ? a_arg1 : a_arg2;
		}



	}
}