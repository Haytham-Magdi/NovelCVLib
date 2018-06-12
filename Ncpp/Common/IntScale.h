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

		static T_Int GetScaleVal(T_Int a_inp)
		{
			return ScaleVal
		}

		static T_Int Scale(T_Float a_fInp)
		{
			return (T_Int)(ScaleVal * a_fInp);
		}

		static T_Float Unscale(T_Int a_scaledInp)
		{
			return ((T_Float)a_scaledInp / ScaleVal);
		}

		static T_Int Round(T_Int a_inp)
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

			nRet /= m_nScale;
			nRet *= m_nScale;

			return nRet;
		}

		static T_Int Ceil(T_Int a_inp)
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

			nRet /= m_nScale;
			nRet *= m_nScale;

			return nRet;
		}

		static T_Int Floor(T_Int a_inp)
		{
			T_Int nRet = a_inp;

			nRet /= m_nScale;
			nRet *= m_nScale;

			return nRet;
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