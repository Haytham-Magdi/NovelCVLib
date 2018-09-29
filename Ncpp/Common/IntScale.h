#pragma once

#pragma inline_depth( 255 )

#include <stdlib.h>


#include <NovelCVLib\Common\Debug.h>




namespace Ncpp
{
	template< class T_Int, class T_Float,  T_Int const ScaleVal>
	class IntScale 
	{
	public :

		static T_Int GetScaleVal()
		{
			return ScaleVal;
		}

		static T_Int ScaleToI(const T_Float a_fInp)
		{
			return (T_Int)(ScaleVal * a_fInp);
		}

		static T_Float UnscaleToF(const T_Int a_scaledInp)
		{
			return ((T_Float)a_scaledInp / ScaleVal);
		}

		static T_Int IntDividByScale(const T_Int a_inp)
		{
			return a_inp / ScaleVal;
		}

		static T_Int Round(const T_Int a_inp)
		{
			T_Int nRet;

			if (a_inp > 0)
			{
				nRet = (T_Int)(a_inp + m_nRoundAdd);
			}
			else
			{
				nRet = (T_Int)(a_inp - m_nRoundAdd);
			}

			nRet /= ScaleVal;
			nRet *= ScaleVal;

			return nRet;
		}

		static T_Int Ceil(const T_Int a_inp)
		{
			T_Int nRet;

			if (a_inp > 0)
			{
				nRet = (T_Int)(a_inp + m_nCeilAdd);
			}
			else
			{
				nRet = (T_Int)(a_inp - m_nCeilAdd);
			}

			nRet /= ScaleVal;
			nRet *= ScaleVal;

			return nRet;
		}

		static T_Int Floor(const T_Int a_inp)
		{
			T_Int nRet = a_inp;

			nRet /= ScaleVal;
			nRet *= ScaleVal;

			return nRet;
		}

		//static T_Int GoToCeilBy(T_Int a_inp, T_Int a_step)
		static T_Int GoNearCeilByOne(const T_Int a_inp)
		{
			T_Int nRet;

			if (a_inp == SRIntScale::Ceil(a_inp))
			{
				return a_inp;
			}

			if (a_inp > 0)
			{
				return a_inp + 1;
			}
			else
			{
				return a_inp - 1;
			}
		}

	protected:

		static T_Int m_nRoundAdd;
		static T_Int m_nCeilAdd;
		
	};


	template< class T_Int, class T_Float, T_Int const ScaleVal>
	T_Int IntScale< T_Int, T_Float, ScaleVal>::m_nRoundAdd = (T_Int)(ScaleVal * 0.55555555);

	template< class T_Int, class T_Float, T_Int const ScaleVal>
	T_Int IntScale< T_Int, T_Float, ScaleVal>::m_nCeilAdd = (T_Int)(ScaleVal * 0.99999999);

}